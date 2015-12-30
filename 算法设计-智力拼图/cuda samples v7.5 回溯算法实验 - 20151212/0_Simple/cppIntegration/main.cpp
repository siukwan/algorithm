/*
 * Copyright 1993-2015 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */

/* 
 * 关于智力拼图问题的GPU解法
 */

// includes, system
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
// Required to include CUDA vector types
#include <cuda_runtime.h>
#include <vector_types.h>
#include <time.h>  
#include <helper_functions.h>
#include <helper_cuda.h>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// 小锟添加
////////////////////////////////////////////////////////////////////////////////
vector<vector<char>> ReverseGraph(vector<vector<char>>& g);
vector<vector<char>> RotateGraph90(vector<vector<char>>& g);
vector<vector<char>> RotateGraph(vector<vector<char>>& g, int times);
void initGraphs(vector<vector<vector<char>>>&g);

/*记录单个图形的长宽和形状*/
struct GraphNode
{
	char shape[5][5];      //图形的形状，因为bool也占用了1B，所以使用char或者bool都可以
	int x ;                //图形的高度
	int y;                 //图形的宽度
	int fill_x;            //图形的第一个有值的坐标点x
	int fill_y;            //图形的第一个有值的坐标点y
};

/*
 *记录每种图形的变形：
 *包括原始，旋转，翻转；
 *最多有8种
 */
struct GraphFormat
{
	GraphNode format[8];   //图形的变形，最多有8种
	int formatCount;       //图形的变形总数
	char c;                //图形的编号，123456789abc
};

/*
 *存储所有图形
 *一共12种图形
 */
struct GraphAll
{
	GraphFormat graph[12]; //各个图形
	int graphCount;        //图形总量
};

/*
 *需要填充的矩阵数据结构
 *每条GPU线程分配一个
 */
struct MatrixNode{
	char shape[20][20];    //确定了12个初始图形，图形存在3*3大小的，所以小于3的，不存在答案。至少从3*20开始，所以形状大小直接定义为20*20
	int x, y;              //矩阵的长宽
	bool solution[12][8];  //矩阵的下一个方案的可能性
	bool graphUsed[12];    //记录12个图形的使用情况
	int thisLevelCount;    //以当前矩阵为基础，能够填充新图形的总数
	int depth;             //层的深度，也相当于已经填充了多少个图形
};


//进行函数声明
void  PrintTitle();
void  printAllGraphStruct();
int   initCUDAandShowMessage();
bool  CinParameters(int&m, int&n);
void  initGraphStruct(GraphAll&cpu_graph);
void  initTmpMatAndCinMN(MatrixNode &cpu_mat_tmp);
void  getFirstUnfill_cpu(MatrixNode &g_mat, int &x, int&y);
bool  canFillMatrix_cpu(MatrixNode &g_mat, GraphNode &graph, int&toFill_x, int&toFill_y, int&fill_x, int&fill_y);
void  fillMatrix_cpu(MatrixNode &g_mat, GraphNode &graph, int&toFill_x, int&toFill_y, int&fill_x, int&fill_y, char&c);
void  PrintMatrix_cpu(MatrixNode &g_mat);
void  refreshSolution(MatrixNode *cpu_mat, int & solutionSum, vector<MatrixNode>& result);

extern "C" bool SiukwanTest(GraphAll *const g_graph);
extern "C" void runCUDA(int blocks, int threads, MatrixNode *const g_mat, GraphAll *const g_graph, int*solutionSum);


GraphAll cpu_graph;//cpu图形定义为全局变量


////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	//显示显卡的相关信息
	if (initCUDAandShowMessage() == 0)
	{
		cout << "没有检测到Nvida显卡及CUDA！" << endl;
		cout << "解决方案：" << endl;
		cout << "1.请使用安装有Nvida显卡即CUDA toolkit 7.5的电脑进行运行该程序" << endl;
		cout << "2.请直接运行CPU版本程序：单线程及多线程程序.exe" << endl;
		getchar();
		return 0;
	}

	//初始化图形的结构体，预先计算出12个图形的各种变形，并存储到cpu_graph
	initGraphStruct(cpu_graph);

	//定义gpu的变量，这个变量在后续的使用中，只会被读取，不需要写入
	GraphAll *gpu_graph;

	//在gpu上分配内存
	cudaMalloc((void **)&gpu_graph, sizeof(cpu_graph));

	//把数据从内存复制到显存
	cudaMemcpy(gpu_graph, &cpu_graph, sizeof(cpu_graph), cudaMemcpyHostToDevice);

	//把在gpu中处理完毕的数据从显存复制到内存
	cudaMemcpy(&cpu_graph, gpu_graph, sizeof(cpu_graph), cudaMemcpyDeviceToHost);
	

	//打印题目和组别信息
	PrintTitle();

	//循环等待输入
	while (1)
	{
		//矩阵变量
		MatrixNode cpu_mat_tmp;

		//初始化矩阵
		initTmpMatAndCinMN(cpu_mat_tmp);

		//定义遍历情况的总数变量的指针
		int *solutionSum = new int[1];

		//初始化遍历12种情况，因为一共有12个初始的图形
		solutionSum[0] = 12;

		//定义各个阶段需要开启的block和thread数量，即线程块和每个线程块上面的数量
		vector<int>blocks = { 16, 256, 256, 256, 256, 512, 512, 1024, 1024, 1024, 1024, 1024, 0 };
		vector<int>threads = { 1, 256, 256, 256, 256, 512, 1024, 1024, 1024, 1024, 1024, 1024, 0 };

		//分配空间给cpu_mat，每个线程占用一个cpu_mat
		MatrixNode *cpu_mat = new MatrixNode[solutionSum[0]];
		//初始化每个cpu_mat
		for (int i = 0; i < solutionSum[0]; i++)
			cpu_mat[i] = cpu_mat_tmp;

		//定义gpu_mat
		MatrixNode *gpu_mat;
		//存储最终答案
		vector<MatrixNode> result(0);


		//windows运行进行时间统计
		time_t  StartTime;
		time_t  EndTime;
		double  TimeUse = 0;
		time(&StartTime);

		//进行层序遍历，一共12个图形，即12层，实际上是宽度优先搜索
		for (int gpuTimes = 0; gpuTimes < 12; gpuTimes++)
		{
			//显示当前的层编号，cpu_mat占用的内存空间，需要遍历的情况数，和最大开启的线程数
			printf("\n%2d：使用内存：%.4fMB\n    遍历：%d，最大线程数为：%d\n", gpuTimes, (float)(sizeof(MatrixNode)*solutionSum[0] / 1000000.0), solutionSum[0], blocks[gpuTimes] * threads[gpuTimes]);

			//答案清零
			result.clear();
			
			//内部循环次数
			int times = 0;

			//剩余需要遍历的情况数量
			int leftSolutionSum = solutionSum[0];

			//开启的线程数量
			int threadSum = blocks[gpuTimes] * threads[gpuTimes];

			//需要遍历的情况数会超出GPU一次性开启的线程数，所以使用串行的方法进行划分
			while (leftSolutionSum != 0)
			{
				//这次需要遍历的情况数量
				int thisSolutionSum;

				//剩余需要遍历的情况数量少于等于这次开启的线程数量，则进行最后一次遍历
				if (leftSolutionSum <= threadSum)
				{
					thisSolutionSum = leftSolutionSum;
					leftSolutionSum = 0;
				}
				//剩余需要遍历的情况数量大于这次开启的线程数量，则开启最大的线程数
				else
				{
					thisSolutionSum = threadSum;
					leftSolutionSum -= threadSum;
				}

				//打印当前执行的步骤数，及使用显存的情况和遍历情况数量
				printf("    -->步骤%d：显存：%.2fMB，遍历：%d\n", times, (float)(sizeof(MatrixNode)*thisSolutionSum / 1000000.0), thisSolutionSum);

				//gpu_solutionSum记录了需要遍历的情况数
				int *gpu_solutionSum;

				//在gpu上分配内存
				cudaMalloc((void **)&gpu_solutionSum, sizeof(int) * 1);

				//把数据从内存复制到显存
				cudaMemcpy(gpu_solutionSum, &thisSolutionSum, sizeof(int) * 1, cudaMemcpyHostToDevice);

				//在gpu上分配内存
				cudaMalloc((void **)&gpu_mat, sizeof(MatrixNode)*thisSolutionSum);

				//cpu_mat的数据从内存复制到显存，主要需要加上偏移量 times*threadSum
				cudaMemcpy(gpu_mat, cpu_mat + times*threadSum, sizeof(MatrixNode)*thisSolutionSum, cudaMemcpyHostToDevice);


				////////////////////////////////////////////////////////////////////////////////
				// 核心代码：进行宽度搜索，遍历各种情况
				////////////////////////////////////////////////////////////////////////////////
				runCUDA(blocks[gpuTimes], threads[gpuTimes], gpu_mat, gpu_graph, gpu_solutionSum);


				//把数据从显存复制到内存
				cudaMemcpy(cpu_mat + times*threadSum, gpu_mat, sizeof(MatrixNode)*thisSolutionSum, cudaMemcpyDeviceToHost);

				//释放相关变量的显存
				cudaFree(gpu_mat);
				cudaFree(gpu_solutionSum);


				//临时答案存储变量
				vector<MatrixNode> tmpResult(0);

				//调用函数更新答案
				refreshSolution(cpu_mat + times*threadSum, thisSolutionSum, tmpResult);

				//汇集答案到result变量
				for (int i = 0; i < (int)tmpResult.size(); i++)
				{
					result.push_back(tmpResult[i]);
				}

				//内部循环次数+1
				times++;
			}

			
			//下次需要遍历的情况总数为此次答案的数量
			solutionSum[0] = (int)result.size();


			//不是最后一次，则需要计算
			if (gpuTimes != blocks.size() - 1)
			{
				//释放cpu_mat的内存
				free(cpu_mat);
				//申请新的内存区域，必须要连续
				cpu_mat = new MatrixNode[solutionSum[0]];
				//把result的变量复制过去
				for (int i = 0; i < solutionSum[0]; i++)
					cpu_mat[i] = result[i];
			}
		}

		//输出最终答案个数
		printf("\n最终答案个数：%d\n\n", (int)result.size());

		//windows运行进行时间统计
		time(&EndTime);
		TimeUse = difftime(EndTime, StartTime);
		cout << "总花费时间为：" << (int)TimeUse / 60 << "分" << ((int)TimeUse) % 60 << "秒" << endl;

		//释放cpu_mat的内存
		free(cpu_mat);

		//如果有需要，可以在这里进行result的输出

	}

    // cudaDeviceReset causes the driver to clean up all state. While
    // not mandatory in normal operation, it is good practice.  It is also
    // needed to ensure correct operation when the application is being
    // profiled. Calling cudaDeviceReset causes all profile data to be
    // flushed before the application exits
    cudaDeviceReset();
    exit(1);
}



/*
函数名  ：initTmpMatAndCinMN
函数功能：初始化cpu_mat_tmp模版，并读取用户输入的矩阵长宽信息，把m和n记录在模版上
输入参数：
cpu_mat_tmp:需要初始化的矩阵模版
*/
void initTmpMatAndCinMN(MatrixNode &cpu_mat_tmp)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
			cpu_mat_tmp.shape[i][j] = 0;
	}
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cpu_mat_tmp.solution[i][j] = 0;
		}
		cpu_mat_tmp.graphUsed[i] = false;
	}
	int m, n;
	while (!CinParameters(m, n))
	{
	}
	//设置长宽
	if (m > n)
	{
		cpu_mat_tmp.x = m;
		cpu_mat_tmp.y = n;
	}
	else
	{
		cpu_mat_tmp.x = n;
		cpu_mat_tmp.y = m;
	}
	cpu_mat_tmp.depth = 0;
	cpu_mat_tmp.thisLevelCount = 0;
}


/*
函数名  ：refreshSolution
函数功能：把cpu_mat中记录的离散的下一次能遍历的情况，存储到result中，并且根据cpu_mat中记录的信息对矩阵进行填充
输入参数：
cpu_mat     :需要读取的矩阵指针（数组），这些矩阵包含了它的下一次能填充图形的情况和信息
solutionSum :cpu_mat数组的大小
result      :又cpu_mat计算出来的新的矩阵情况
*/
void refreshSolution(MatrixNode *cpu_mat, int & solutionSum, vector<MatrixNode>& result)
{
	for (int i = 0; i < solutionSum; i++)
	{
		if (cpu_mat[i].thisLevelCount != 0)
		{//遍历它的情况，并压入新的容器中

			//找出这个图形没有填充的部分
			int unfill_x = -1;
			int unfill_y = -1;
			getFirstUnfill_cpu(cpu_mat[i], unfill_x, unfill_y);

			//遍历12种图形
			for (int type = 0; type < 12; type++)
			{
				//遍历8种变形
				for (int transform = 0; transform < 8; transform++)
				{
					//如果存在，则压进容器
					if (cpu_mat[i].solution[type][transform] != 0)
					{
						//记录临时图形
						MatrixNode tmpMat = cpu_mat[i];
						//标记已经使用的图案
						tmpMat.graphUsed[type] = true;

						//清楚计数
						tmpMat.thisLevelCount = 0;

						//把所有的解决方案清零
						for (int tmpType = 0; tmpType < 12; tmpType++)
							for (int tmpTransform = 0; tmpTransform < 8; tmpTransform++)
								tmpMat.solution[tmpType][tmpTransform] = false;
						//把图形填充到矩阵中
						fillMatrix_cpu(tmpMat, cpu_graph.graph[type].format[transform], unfill_x, unfill_y, cpu_graph.graph[type].format[transform].fill_x, cpu_graph.graph[type].format[transform].fill_y, cpu_graph.graph[type].c);
						result.push_back(tmpMat);

					}
				}
			}
		}
	}
}


/*
函数名  ：PrintTitle
函数功能：打印题目及组别信息
*/
void PrintTitle()
{
	cout << "|---------------------------------------------------------------|\n";
	cout << "|                  算法实现题7:智力拼图问题                     |\n";
	cout << "|                                                               |\n";
	cout << "| 设有12个平面图形（1,2,3,4,5,6,7,8,9，a,b,c）如下图所示。      |\n";
	cout << "| 每个图形的形状互不相同，但它们都是由5个大小相同的正方形组成。 |\n";
	cout << "| 如下图中这12个图形拼接成一个6*10的矩阵。                      |\n";
	cout << "| 计算出用这12个图形拼接成给定矩形的拼接方案.                   |\n";
	cout << "|                     _________________                         |\n";
	cout << "|                    |__  6 _____|  |  |                        |\n";
	cout << "|                    |  |__|c ______|1 |                        |\n";
	cout << "|                    |  |  |__|________|                        |\n";
	cout << "|                    |a |__ 5 |   __ 2 |                        |\n";
	cout << "|                    |  |  |  |__|  |__|                        |\n";
	cout << "|                    |__|7 |__|__ 8  __|                        |\n";
	cout << "|                    |________|  |__|  |                        |\n";
	cout << "|                    |  |__ 9  __| b __|                        |\n";
	cout << "|                    |  3  |__|_____|4 |                        |\n";
	cout << "|                    |_____|___________|                        |\n";
	cout << "|                                                               |\n";
	cout << "|                          第七组                               |\n";
	cout << "|               李小锟15213068 毛亚芳15213097                   |\n";
	cout << "|               骆顺昌15213042 周昱志15213065                   |\n";
	cout << "|---------------------------------------------------------------|\n";
	cout << "|                                                               |\n";
	cout << "|                       CUDA运算版本                            |\n";
	cout << "|                                                               |\n";
	cout << "|---------------------------------------------------------------|\n";
}


/*
函数名  ：CinParameters
函数功能：读取输入的程序运行类型，矩阵长宽，如果合理返回true，否则返回false
输入参数：
runtype:程序运行类型
m      :矩阵宽度
n      :矩阵高度
*/
bool CinParameters( int&m, int&n)
{
	cout << "请输入矩阵的宽度：" << endl;
	cin >> m;
	if (m <= 0)
	{
		cout << "必须为正数，请重新输入!" << endl;
		return false;
	}
	cout << "清输入矩阵的长度：" << endl;
	cin >> n;
	if (n <= 0)
	{
		cout << "必须为正数，请重新输入!" << endl;
		return false;
	}
	if (m*n != 60)
	{
		cout << "m*n不等于60，请重新输入!" << endl;
		return false;
	}
	return true;
}

/*
函数名  ：initCUDAandShowMessage
函数功能：读取显卡信息并进行输出，返回显卡数量信息
*/
int initCUDAandShowMessage()
{/*
 name
 用于标识设备的ASCII字符串；
totalGlobalMem
设备上可用的全局存储器的总量，以字节为单位；
sharedMemPerBlock
线程块可以使用的共享存储器的最大值，以字节为单位；多处理器上的所有线程块可以同时共享这些存储器；
regsPerBlock
线程块可以使用的32位寄存器的最大值；多处理器上的所有线程块可以同时共享这些寄存器；
warpSize
按线程计算的warp块大小；
memPitch
允许通过cudaMallocPitch()为包含存储器区域的存储器复制函数分配的最大间距（pitch），以字节为单位；
maxThreadsPerBlock
每个块中的最大线程数：
maxThreadsDim[3]
块各个维度的最大值：
maxGridSize[3]
网格各个维度的最大值；
totalConstMem
设备上可用的不变存储器总量，以字节为单位； 
major，minor
定义设备计算能力的主要修订号和次要修订号；
clockRate
以千赫为单位的时钟频率；
textureAlignment
对齐要求；与textureAlignment字节对齐的纹理基址无需对纹理取样应用偏移；
deviceOverlap
如果设备可在主机和设备之间并发复制存储器，同时又能执行内核，则此值为 1；否则此值为 0；
multiProcessorCount
设备上多处理器的数量。
 */
	cudaDeviceProp prop;
	int count;
	cudaGetDeviceCount(&count);
	for (int i = 0; i < count; i++)
	{
		cudaGetDeviceProperties(&prop, i);
		cudaDeviceProp sDevProp = prop;
		printf("Device name         : %s\n", sDevProp.name); //用于标识设备的ASCII字符串；
		printf("Device memory       : %d\n", sDevProp.totalGlobalMem);//设备上可用的全局存储器的总量，以字节为单位；
		printf("Memory per-block    : %d\n", sDevProp.sharedMemPerBlock);//线程块可以使用的共享存储器的最大值，以字节为单位；多处理器上的所有线程块可以同时共享这些存储器；
		printf("Register per-block  : %d\n", sDevProp.regsPerBlock);//线程块可以使用的32位寄存器的最大值；多处理器上的所有线程块可以同时共享这些寄存器；
		printf("Warp size           : %d\n", sDevProp.warpSize);//按线程计算的warp块大小；
		printf("Memory pitch        : %d\n", sDevProp.memPitch);//允许通过cudaMallocPitch()为包含存储器区域的存储器复制函数分配的最大间距（pitch），以字节为单位；
		printf("Constant Memory     : %d\n", sDevProp.totalConstMem);//设备上可用的不变存储器总量，以字节为单位； 
		printf("Max thread per-block: %d\n", sDevProp.maxThreadsPerBlock);//每个块中的最大线程数;
		printf("Max thread dim      : ( %d, %d, %d )\n", sDevProp.maxThreadsDim[0],
			sDevProp.maxThreadsDim[1], sDevProp.maxThreadsDim[2]);//
		printf("Max grid size       : ( %d, %d, %d )\n", sDevProp.maxGridSize[0],
			sDevProp.maxGridSize[1], sDevProp.maxGridSize[2]);//
		printf("Ver                 : %d.%d\n", sDevProp.major, sDevProp.minor);//
		printf("Clock               : %d\n", sDevProp.clockRate);//以千赫为单位的时钟频率；
		printf("textureAlignment    : %d\n", sDevProp.textureAlignment);//对齐要求；与textureAlignment字节对齐的纹理基址无需对纹理取样应用偏移；
		printf("多处理器MP的数量    : %d\n", sDevProp.multiProcessorCount);//设备上多处理器的数量
		cudaSetDevice(i);
		printf("\n CUDA initialized.\n");
	}
	return count;
}


/*
函数名  ：RotateGraph90
函数功能：对graph进行旋转90度
输入参数：
g:需要旋转的graph
*/
vector<vector<char>> RotateGraph90(vector<vector<char>>& g)
{//把图形旋转90°
	vector<vector<char>> newG(g[0].size(), vector<char>(g.size()));
	for (int i = 0; i < newG.size(); i++)
	{
		for (int j = 0; j < newG[i].size(); j++)
			newG[i][j] = g[newG[i].size() - 1 - j][i];
	}
	return newG;
}

/*
函数名  ：PrintMatrix_cpu
函数功能：打印cpu端的矩阵
输入参数：
g_mat:需要打印的矩阵
*/
void PrintMatrix_cpu(MatrixNode &g_mat)
{
	for (int i = 0; i < g_mat.x; i++)
	{
		for (int j = 0; j < g_mat.y; j++)
		{
			printf("%c ", g_mat.shape[i][j]);
		}
		printf("\n");
	}
}

/*
函数名  ：RotateGraph
函数功能：对graph进行旋转0度，90度，180度或270度
输入参数：
g    :需要旋转的graph
times:旋转次数，0次表示旋转0度，1次表示旋转90度
*/
vector<vector<char>> RotateGraph(vector<vector<char>>& g, int times)
{//旋转90度多次，实现旋转180度，270度
	vector<vector<char>> newG = g;
	for (int i = 0; i < times; i++)
		newG = RotateGraph90(newG);
	return newG;
}


/*
函数名  ：ReverseGraph
函数功能：对graph进行左右翻转
输入参数：
g:需要翻转的graph
*/
vector<vector<char>> ReverseGraph(vector<vector<char>>& g)
{
	vector<vector<char>> newG = g;
	for (int i = 0; i < newG.size(); i++)
	{
		for (int j = 0; j < newG[i].size(); j++)
			newG[i][j] = g[i][newG[i].size() - 1 - j];
	}
	return newG;
}

/*
函数名  ：initGraphs
函数功能：初始化12个图形
输入参数：
g:需要初始化的图形变量
*/
void initGraphs(vector<vector<vector<char>>>&g)
{
	//存储12个图形
	g =
	{
		{//1
			{ 0, 0, 1 },   //      ||
			{ 0, 0, 1 },   //      ||
			{ 1, 1, 1 }    //  ||||||
		},
		{//2
			{ 1, 1, 1 },   //  ||||||  
			{ 1, 0, 1 }    //  ||  ||
		},
		{//3
			{ 1, 0 },      //  ||
			{ 1, 1 },      //  ||||
			{ 1, 1 }       //  ||||
		},
		{//4
			{ 0, 0, 0, 1 },//        ||
			{ 1, 1, 1, 1 } //  ||||||||
		},
		{//5
			{ 1, 0 },      //  ||
			{ 1, 1 },      //  ||||  
			{ 0, 1 },      //    ||
			{ 0, 1 }       //    ||
		},
		{//6
			{ 1, 1, 1, 1 },//  ||||||||
			{ 0, 1, 0, 0 } //    ||
		},
		{//7
			{ 0, 1, 0 },   //      ||
			{ 0, 1, 0 },   //      ||
			{ 1, 1, 1 }    //  ||||||
		},
		{//8
			{ 0, 1, 0 },   //    ||
			{ 1, 1, 1 },   //  ||||||
			{ 0, 1, 0 }    //    ||
		},
		{//9
			{ 0, 0, 1 },   //      ||
			{ 1, 1, 1 },   //  ||||||
			{ 0, 1, 0 }    //    ||
		},
		{//a
			{ 1 },         //  ||
			{ 1 },         //  ||
			{ 1 },         //  ||
			{ 1 },         //  ||
			{ 1 },         //  ||
		},
		{//b
			{ 0, 0, 1 },   //      ||
			{ 0, 1, 1 },   //    ||||
			{ 1, 1, 0 }    //  ||||
		},
		{//c
			{ 0, 0, 1 },   //      ||
			{ 1, 1, 1 },   //  ||||||
			{ 1, 0, 0 }    //  ||
		}
	};
}
/*
函数名  ：getFirstFill
函数功能：检测graph中第一行有值的位置（坐标）
输入参数：
graph:检测的graph
*/
pair<int, int> getFirstFill(vector<vector<char>>& graph)
{
	pair<int, int> fill = { -1, -1 };
	for (int j = 0; j < graph.size(); j++)
	{
		for (int h = 0; h < graph[j].size(); h++)
		{//找出第一个未填的位置，记录下来，直接跳出
			if (graph[j][h] != 0)
			{//不为0，即有值
				fill = { j, h };
				break;
			}
		}
		if (fill.first != -1) break;
	}
	return fill;
}

/*
函数名  ：int2char
函数功能：把整型转化为题目相应的char,0显示为1，9显示为a
输入参数：
a:需要转换的整型
*/
char int2char(int a)
{
	if (a < 9) return a + '1';
	else return a - 9 + 'a';
}

/*
函数名  ：getFirstUnfill
函数功能：检测矩阵mat中第一个空白的格子（坐标）
输入参数：
mat:检测的mat
*/
void getFirstUnfill_cpu(MatrixNode &g_mat, int &x, int&y)
{
	for (int i = 0; i <g_mat.x; i++)
	{
		for (int j = 0; j < g_mat.y; j++)
		{//找出第一个未填的位置，记录下来，直接跳出
			if (g_mat.shape[i][j] == 0)
			{//为0，即没有填充
				x = i;
				y = j;
				break;//找到第一个就马上跳出
			}
		}
		if (x != -1) break;
	}
}



/*
函数名  ：initGraphStruct
函数功能：初始化12个图形的各种变形，并存储到结构体cpu_graph中
输入参数：
cpu_graph:需要初始化的图形变量结构体
*/
void initGraphStruct(GraphAll&cpu_graph)
{
	//存储12个图形
	vector<vector<vector<char>>> graph_vector;
	//先初始化这12个图形的基本状态
	initGraphs(graph_vector);
	//cpu_graph.graph = new GraphFormat[12];
	cpu_graph.graphCount = 12;
	for (int type = 0; type < 12; type++)
	{
		vector<vector<vector<char>>> allGraph(0);//记录所有的类型
		map<vector<vector<char>>, bool> checkDuplicate;//检查重复
		vector<vector<char>> transGraph; //变化后的图片
		for (int i = 0; i < 4; i++)
		{//进行4个角度的变换
			transGraph = RotateGraph(graph_vector[type], i);
			for (int j = 0; j < 2; j++)
			{
				if (j == 1)//0不翻转，1为翻转
					transGraph = ReverseGraph(transGraph);
				if (checkDuplicate[transGraph] == 0)
				{//没有重复的才压进答案
					checkDuplicate[transGraph] = 1;
					allGraph.push_back(transGraph);
				}
			}
		}
		cpu_graph.graph[type].formatCount = (int)allGraph.size();
		cpu_graph.graph[type].c = int2char(type);
		for (int k = 0; k < allGraph.size(); k++)
		{
			cpu_graph.graph[type].format[k].x = (int)allGraph[k].size();
			cpu_graph.graph[type].format[k].y = (int)allGraph[k][0].size();
			pair<int, int> fill = getFirstFill(allGraph[k]);
			cpu_graph.graph[type].format[k].fill_x = fill.first;
			cpu_graph.graph[type].format[k].fill_y = fill.second;
			for (int i = 0; i < (int)allGraph[k].size(); i++)
			{
				for (int j = 0; j < (int)allGraph[k][i].size(); j++)
				{
					cpu_graph.graph[type].format[k].shape[i][j] = allGraph[k][i][j];
				}
			}
		}

	}

}

/*
函数名  ：printAllGraphStruct
函数功能：打印cpu_graph中的所有图形
*/
void printAllGraphStruct()
{
	for (int i = 0; i < cpu_graph.graphCount; i++)
	{
		printf("\n图形%d共%d种变形：\n\n", i, cpu_graph.graph[i].formatCount);

		//遍历所有的变形
		for (int j = 0; j < cpu_graph.graph[i].formatCount; j++)
		{
			for (int k = 0; k < cpu_graph.graph[i].format[j].x; k++)
			{
				for (int h = 0; h < cpu_graph.graph[i].format[j].y; h++)
				{//输出每个像素点
					cout << cpu_graph.graph[i].format[j].shape[k][h] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}
}


/*
函数名  ：canFillMatrix_cpu
函数功能：图案能否填充到矩阵中
输入参数：
g_mat    :被填充的矩阵
graph    :用来填充的图形
toFill_x :被填充矩阵的第一个空格位置x
toFill_y :被填充矩阵的第一个空格位置y
fill_x   :填充的图形的第一个非空格位置x
fill_y   :填充的图形的第一个非空格位置y
*/
bool canFillMatrix_cpu(MatrixNode &g_mat, GraphNode &graph, int&toFill_x, int&toFill_y, int&fill_x, int&fill_y)
{//判断图案能否填充到矩阵中，其中矩阵的第一个空白点坐标为toFill


	for (int i = 0; i < graph.x; i++)
	{
		for (int j = 0; j < graph.y; j++)
		{
			if (i + toFill_x - fill_x >= g_mat.x ||
				j + toFill_y - fill_y >= g_mat.y ||
				i + toFill_x - fill_x < 0 ||
				j + toFill_y - fill_y < 0
				)
			{//图形填充后越界，返回false
				return false;
			}
			else if (graph.shape[i][j] != 0 && g_mat.shape[i + toFill_x - fill_x][j + toFill_y - fill_y] != 0)
			{//图形填充的部分不为空，返回false
				return false;
			}
		}
	}
	return true;
}

/*
函数名  ：fillMatrix_cpu
函数功能：把图案填充到矩阵中
输入参数：
g_mat    :被填充的矩阵
graph    :用来填充的图形
toFill_x :被填充矩阵的第一个空格位置x
toFill_y :被填充矩阵的第一个空格位置y
fill_x   :填充的图形的第一个非空格位置x
fill_y   :填充的图形的第一个非空格位置y
c        :填充的图形的字符
*/
void fillMatrix_cpu(MatrixNode &g_mat, GraphNode &graph, int&toFill_x, int&toFill_y, int&fill_x, int&fill_y, char&c)
{//对矩阵进行填充
	for (int i = 0; i < graph.x; i++)
	{
		for (int j = 0; j < graph.y; j++)
		{
			if (graph.shape[i][j] != 0)
			{//暂时符合要求，进行填充
				g_mat.shape[i + toFill_x - fill_x][j + toFill_y - fill_y] = c;
			}
		}
	}
}
