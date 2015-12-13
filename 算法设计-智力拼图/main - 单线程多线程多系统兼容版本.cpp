//#include<string>
//#include <iomanip>
#include<fstream>
//#include<set>
//#include<queue>
#include<map>
//#include<unordered_set>
//#include<unordered_map>
//#include <sstream>
//#include "func.h"
//#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
//#include<stack>
#include<vector>
#include <algorithm>
#ifdef WIN32

#include <time.h>  
#include <windows.h> 
#include <tchar.h>

#else

#include <sys/time.h>
#include <pthread.h>
#endif


using namespace std;
/*
运行类型
0：矩阵不旋转，图形旋转+翻转，剪枝
1：矩阵旋转  ，图形旋转+翻转，剪枝
2：矩阵不旋转，图形旋转+翻转，直接暴力搜索
3：矩阵不旋转，图形旋转+翻转，多线程
*/
int RunType = 0;
vector<string> TypeStr = { "normal", "rotate", "violence", "threads" };

//存储12个图形
vector<vector<vector<char>>> graph;
unsigned long long TotalCounter = 0;
map<vector<vector<char>>, char> AnswerCheck;

string               int2str(int a);
char                 int2char(int a);

void                 PrintTitle();
bool                 isAllThreadsFinished();
bool                 CinParameters(int&runtype, int&m, int&n);
void                 initGraphs(vector<vector<vector<char>>>&g);

void                 PrintMatrix(vector<vector<char>> m);
pair<int, int>       getFirstUnfill(vector<vector<char>>&mat);
pair<int, int>       getFirstFill(vector<vector<char>>& graph);
vector<vector<char>> ReverseGraph(vector<vector<char>>& g);
vector<vector<char>> RotateGraph90(vector<vector<char>>& g);
vector<vector<char>> RotateGraph(vector<vector<char>>& g, int times);
bool                 fillMatrix(vector<vector<char>>&mat, vector<vector<char>> graphToFill, pair<int, int> toFill, char c);
void                 dfs(int sum, vector<bool>& used, vector<vector<char>> mat, vector<vector<vector<char>>>&answer, int StartGraphIdx, unsigned long long &Counter);

//记录正在运行的线程数量
int RunningThreadSum;
//记录开启的线程图形
int GraphIdx;
//下面的变量每条线程占用独自的一个变量
vector<vector<bool>> ThreadUsed;//记录图形是否被使用
vector<vector<vector<char>>> ThreadMat;//记录线程自身的矩阵
vector<vector<vector<vector<char>>>> ThreadAnswer;//记录各个线程的答案，最终进行累加统计
vector<bool> ThreadFinished;//记录各个线程是否完成
vector<unsigned long long> ThreadCounter;//记录各个线程遍历的情况

#define CPU_THREAD_COUNT 17

#ifdef WIN32
//windows多线程
int PrintfThreshold = 1000;

//创建互斥变量
HANDLE RunningThreadSumMutex = CreateMutex(NULL, FALSE, _T("RunningThreadSum"));
HANDLE GraphIdxMutex         = CreateMutex(NULL, FALSE, _T("GraphIdx"));

DWORD WINAPI dfsThread(LPVOID lpParamter)
{
	//互斥访问GraphIdx，并复制当前的GraphIdx，避免后面出现被其他线程更改的情况
	WaitForSingleObject(GraphIdxMutex, INFINITE);
	int tmpIdx = GraphIdx;
	GraphIdx++;
	ReleaseMutex(GraphIdxMutex);

	printf("\n|---------------------------------------------------------------|\n");
	printf(  "|                          开启%02d线程                           |\n", tmpIdx);
	printf(  "|---------------------------------------------------------------|\n\n");

	//进行深度搜索
	dfs(0, ThreadUsed[tmpIdx], ThreadMat[tmpIdx], ThreadAnswer[tmpIdx], tmpIdx, ThreadCounter[tmpIdx]);

	//线程工作完成
	WaitForSingleObject(RunningThreadSumMutex, INFINITE);
	RunningThreadSum--;
	ReleaseMutex(RunningThreadSumMutex);
	ThreadFinished[tmpIdx] = true;

	printf("\n|---------------------------------------------------------------|\n");
	printf(  "|XXXXXXXXXXXXXXXXXXXXXX    结束%02d线程    XXXXXXXXXXXXXXXXXXXXXXX|\n", tmpIdx);
	printf(  "|---------------------------------------------------------------|\n\n");
	return 1;
}
#else
int PrintfThreshold = 1000000;

//创建互斥变量
pthread_mutex_t RunningThreadSumMutex;
pthread_mutex_t GraphIdxMutex;

void *dfsThread(void *arg)
{
	//互斥访问GraphIdx，并复制当前的GraphIdx，避免后面出现被其他线程更改的情况
	pthread_mutex_lock(&GraphIdxMutex); // 给互斥体变量加锁 
	int tmpIdx = GraphIdx;
	GraphIdx++;
	pthread_mutex_unlock(&GraphIdxMutex); // 给互斥体变量解除锁

	printf("\n|---------------------------------------------------------------|\n");
	printf(  "|                          开启%02d线程                           |\n", tmpIdx);
	printf(  "|---------------------------------------------------------------|\n\n");

	//进行深度搜索
	dfs(0, ThreadUsed[tmpIdx], ThreadMat[tmpIdx], ThreadAnswer[tmpIdx], tmpIdx, ThreadCounter[tmpIdx]);

	//线程工作完成
	pthread_mutex_lock(&RunningThreadSumMutex); // 给互斥体变量加锁 
	RunningThreadSum--;
	pthread_mutex_unlock(&RunningThreadSumMutex); // 给互斥体变量解除锁
	ThreadFinished[tmpIdx] = true;

	printf("\n|---------------------------------------------------------------|\n");
	printf("|XXXXXXXXXXXXXXXXXXXXXX    结束%02d线程    XXXXXXXXXXXXXXXXXXXXXXX|\n", tmpIdx);
	printf("|---------------------------------------------------------------|\n\n");
}

#endif




/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	//打印题目和组别信息
	PrintTitle();
	//初始化12个图形
	initGraphs(graph);
	while (1)
	{
		int m, n;
		if (!CinParameters(RunType, m, n))
			continue;
		TotalCounter = 0;
		AnswerCheck.clear();
#ifdef WIN32
		//windows运行进行时间统计
		time_t  StartTime;
		time_t  EndTime;
		double  TimeUse = 0;
		time(&StartTime);
#else
		if(m==6||n==6)
			PrintfThreshold = 5000000;
		else if(m==5||n==5)
			PrintfThreshold = 2000000;
		//linux运行进行时间统计
		struct timeval StartTime;
		struct timeval EndTime;
		double TimeUse = 0;
		gettimeofday(&StartTime, NULL);

		//按缺省的属性初始化互斥体变量mutex 
		pthread_mutex_init(&RunningThreadSumMutex, NULL); 
		pthread_mutex_init(&GraphIdxMutex, NULL); 
#endif


		//使用二维数组来存储期望矩阵
		vector<vector<char>> mat(n, vector<char>(m, 0));
		//记录图形是否使用过,一共12个图形
		vector<bool> used(12, false);
		//记录答案
		vector<vector<vector<char>>> answer;


		//多线程运行
		if (RunType == 3)
		{

			ThreadUsed          = vector<vector<bool>>(12, used);
			ThreadMat           = vector<vector<vector<char>>>(12, mat);
			ThreadAnswer        = vector<vector<vector<vector<char>>>>(12);
			ThreadFinished      = vector<bool>(12, false);//记录各个线程是否完成
			ThreadCounter       = vector<unsigned long long>(12, 0);//记录各个线程遍历的情况
			GraphIdx            = 0;
			RunningThreadSum    = 0;
			int openThreadCount = 0;
			while (openThreadCount<12)
			{//开启12条线程
				if (RunningThreadSum < CPU_THREAD_COUNT)
				{//开启12条线程，如果能够开线程
#ifdef WIN32
					WaitForSingleObject(RunningThreadSumMutex, INFINITE);
					RunningThreadSum++;
					openThreadCount++;
					ReleaseMutex(RunningThreadSumMutex);
					//开线程：
					HANDLE hThread = CreateThread(NULL, 0, dfsThread, NULL, 0, NULL);
					Sleep(1);
#else
					pthread_mutex_lock(&RunningThreadSumMutex); // 给互斥体变量加锁 
					RunningThreadSum++;
					openThreadCount++;
					pthread_mutex_unlock(&RunningThreadSumMutex); // 给互斥体变量解除锁
					//开线程：
					pthread_t tid;
					pthread_create(&tid, NULL, dfsThread, NULL);
					usleep(1);
#endif
				}
				else//不能开线程
					while (RunningThreadSum >= CPU_THREAD_COUNT);
			}


			//检测所有的进程是否已经完成
			while (!isAllThreadsFinished());


			//统计和合并答案
			for (int i = 0; i < 12; i++)
			{
				//记录各个线程统计的数量
				TotalCounter += ThreadCounter[i];
				printf("线程%2d遍历的情况总数：%10d，答案个数：%d\n", i, (int)ThreadCounter[i], (int)ThreadAnswer[i].size());
				//合并答案
				for (int j = 0; j < ThreadAnswer[i].size(); j++)
					answer.push_back(ThreadAnswer[i][j]);
			}

		}
		else
		{//单线程运行,-1表示不指定第一个填充的图形
			dfs(0, used, mat, answer, -1,TotalCounter);
		}

#ifdef WIN32
		//windows运行进行时间统计
		time(&EndTime);
		TimeUse = difftime(EndTime, StartTime);
		cout << "总花费时间为：" << (int)TimeUse / 60 << "分" << ((int)TimeUse ) % 60 << "秒" << endl;
#else
		//linux运行进行时间统计
		gettimeofday(&EndTime, NULL);
		TimeUse = 1000000 * (EndTime.tv_sec - StartTime.tv_sec) + EndTime.tv_usec - StartTime.tv_usec;
		TimeUse /= 1000;
		cout << "总花费时间为：" << TimeUse << "ms" << endl;
		cout << "总花费时间为：" << TimeUse / 1000 << "s" << endl;
		cout << "总花费时间为：" << (int)(TimeUse / 1000) / 60 << "分" << ((int)(TimeUse / 1000)) % 60 << "秒" << endl;
#endif




		cout << "共遍历了" << TotalCounter << "种情况。" << endl;
		cout << "答案个数：" << answer.size() << endl;
		cout << "正在写入文件中..." << endl;
		//建议换成存储成文件
		ofstream outFile(int2str(m) + "x" + int2str(n) + "answer_" + TypeStr[RunType] + ".txt", ios::out);

		outFile << "共遍历了" << TotalCounter << "种情况。" << endl;
		outFile << "答案个数：" << answer.size() << endl;


#ifdef WIN32
		outFile << "总花费时间为：" << (int)TimeUse / 60 << "分" << ((int)TimeUse) % 60 << "秒" << endl;
#else
		outFile << "总花费时间为：" << TimeUse << "ms" << endl;
		outFile << "总花费时间为：" << TimeUse / 1000 << "s" << endl;
		outFile << "总花费时间为：" << (int)(TimeUse / 1000) / 60 << "分" << ((int)(TimeUse / 1000)) % 60 << "秒" << endl;
#endif
		for (int m = 0; m < answer.size(); m++)
		{
			for (int i = 0; i < answer[m].size(); i++)
			{
				for (int j = 0; j < answer[m][i].size(); j++)
					outFile << answer[m][i][j];
				outFile << endl;
			}
			outFile << endl << endl;
		}
		outFile.close();
		cout << "已经写入到answer_" + TypeStr[RunType] + ".txt文件中。" << endl;
	}
	return  0;
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
}


/*
函数名  ：CinParameters
函数功能：读取输入的程序运行类型，矩阵长宽，如果合理返回true，否则返回false
输入参数：
runtype:程序运行类型
m      :矩阵宽度
n      :矩阵高度
*/
bool CinParameters(int&runtype ,int&m,int&n)
{
	//程序类型，矩阵参数输入
	cout << "请输入程序运行类型（0为单线程运行，3为多线程运行），如不清楚请直接输入0：" << endl;
	cin >> runtype;
	if (runtype >= TypeStr.size())
	{
		cout << "必须小于" << TypeStr.size() << endl;
		return false;
	}
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
函数名  ：int2str
函数功能：把int转为string
输入参数：
a:转换的int型数字
*/
string int2str(int a)
{
	string result = "";
	if (a == 0) return "0";
	while (a != 0)
	{
		char c = a % 10 + '0';
		result = c + result;
		a /= 10;
	}
	return result;
}
/*
函数名  ：isAllThreadsFinished
函数功能：检测是否所有的进程都已经完成工作
*/
bool isAllThreadsFinished()
{
	int FinishedCount = 0;
	for (int i = 0; i < ThreadFinished.size(); i++)
		FinishedCount += ThreadFinished[i];
	if (FinishedCount == ThreadFinished.size())
		return true;
	return false;
}

/*
函数名  ：int2char
函数功能：把graph的index转换成graph的编号：123456789abc
输入参数：
a:graph的index
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
pair<int, int> getFirstUnfill(vector<vector<char>>&mat)
{
	pair<int, int> unfill = { -1, -1 };
	for (int j = 0; j < mat.size(); j++)
	{
		for (int h = 0; h < mat[j].size(); h++)
		{//找出第一个未填的位置，记录下来，直接跳出
			if (mat[j][h] == 0)
			{//为0，即没有填充
				unfill = { j, h };
				break;
			}
		}
		if (unfill.first != -1) break;
	}
	return unfill;
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
函数名  ：PrintMatrix
函数功能：输出m到命令行（打印矩阵）
输入参数：
m:需要打印的矩阵
*/
void PrintMatrix(vector<vector<char>> m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
			cout << m[i][j];
		cout << endl;
	}
	cout << endl << endl;
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
函数名  ：fillMatrix
函数功能：判断graph[i]能否填充到mat中，如果能够填充，返回true并更新mat；如果不能则返回false，且不对mat处理
输入参数：
mat        :现在填充的矩阵
graphToFill:需要填充的graph
toFill     :mat的第一个空位（即需要填充的第一个空格的坐标）
c          :graph的编号，如1，2，3，....，a，b，c

*/
bool fillMatrix(vector<vector<char>>&mat, vector<vector<char>> graphToFill, pair<int, int> toFill, char c)
{//判断图案能否填充到矩阵中，其中矩阵的第一个空白点坐标为toFill

	vector<vector<char>> newMat = mat;
	bool canFill = true;

	//找出图形第一个可以填充的点
	pair<int, int> fill = getFirstFill(graphToFill);

	for (int i = 0; i < graphToFill.size(); i++)
	{
		for (int j = 0; j < graphToFill[i].size(); j++)
		{
			if (i + toFill.first - fill.first >= mat.size() ||
				j + toFill.second - fill.second >= mat[i + toFill.first].size() ||
				i + toFill.first - fill.first < 0 ||
				j + toFill.second - fill.second < 0
				)
			{//图形填充后越界，返回false
				canFill = false;
				break;
			}
			else if (graphToFill[i][j] != 0 && mat[i + toFill.first - fill.first][j + toFill.second - fill.second] != 0)
			{//图形填充的部分不为空，返回false
				canFill = false;
				break;
			}

			else if (graphToFill[i][j] == 0 && i == 0 && j == 0 && toFill.first == 0 && toFill.second == 0)
			{//图形无法填充第一个缺失的格子，返回false
				canFill = false;
				break;
			}
			else if (graphToFill[i][j] != 0)
			{//暂时符合要求，进行填充
				newMat[i + toFill.first - fill.first][j + toFill.second - fill.second] = c;
			}

		}
		if (!canFill) break;
	}
	if (canFill)
	{//填充成功
		mat = newMat;
		return true;
	}
	else//填充失败
		return false;
}

/*
函数名  ：dfs
函数功能：进行深度搜索寻找合适的答案
输入参数：
sum          :当前已经填充图形的个数
used         :记录第i个图形是否已经使用
mat          :现在填充的矩阵
answer       :最终的答案
StartGraphIdx:指定的第一个填充图形的index，-1表示不指定
*/
void dfs(int sum, vector<bool>& used, vector<vector<char>> mat, vector<vector<vector<char>>>&answer, int StartGraphIdx, unsigned long long &Counter)
{
	if (Counter % PrintfThreshold == 0 && sum != 0)
	{
		if (StartGraphIdx != -1)
			printf("线程%2d：正在运行，已经遍历了%10lld种情况，答案个数为：%d\n", StartGraphIdx, Counter, (int)answer.size());
		else
			printf("正在运行，已经遍历了%10lld种情况，答案个数为：%d\n", Counter, (int)answer.size());
	}

	if (sum == 12)
	{//如果已经填充了12个图形，则为正确答案
		if (AnswerCheck[mat] == 0)
		{//避免重复的答案
			AnswerCheck[mat] = 1;
			answer.push_back(mat);
		}
	}
	else
	{
		for (int i = 0; i < graph.size(); i++)
		{
			if (sum == 0 && StartGraphIdx != -1 && StartGraphIdx != i)
				continue;//如果是第一个图形，且指定了idx，则需要continue到合适的idx
			if (!used[i])
			{

				//把图案旋转
				if (RunType == 1)
					mat = RotateGraph90(mat);
				//找出mat中第一个没有被填充的空格
				pair<int, int> unfill = getFirstUnfill(mat);

				if (RunType != 2)
				{//除了状态2，其他都是需要剪枝
					int block = 0;
					if (unfill.first == 0 || mat[unfill.first - 1][unfill.second] != 0)
						block++;
					if (unfill.second == 0 || mat[unfill.first][unfill.second - 1] != 0)
						block++;
					if (unfill.first == mat.size() - 1 || mat[unfill.first + 1][unfill.second] != 0)
						block++;
					if (unfill.second == mat[0].size() - 1 || mat[unfill.first][unfill.second + 1] != 0)
						block++;
					if (block == 4)
						continue;//周围4个都是已经填充，直接跳过这次遍历
				}


				//建立一个局部的矩阵，用于还原mat
				vector<vector<char>> newMat = mat;

				//遍历4个角度的graph
				for (int rotate = 0; rotate < 4; rotate++)
				{//把图形添加到矩阵中，看是否能够添加
					if (RunType != 2 && ((i == 7 && rotate >= 1) || (i == 9 && rotate >= 2)))
						continue;
					for (int reverse = 0; reverse < 2; reverse++)
					{
						vector<vector<char>> transformGraph = RotateGraph(graph[i], rotate);
						if (reverse == 1)//等于1的时候进行翻转
						{//在reverse==0的时候，已经遍历了未翻转的情况，现在需要排除一些翻转后重复的情况
							if (RunType != 2 && (i == 0 || i == 1 || i == 6 || i == 7 || i == 9 || i == 10))
								continue;//1，2，7，8，a，b在任何状态下的翻转都会与部分旋转状态重复
							transformGraph = ReverseGraph(transformGraph);
						}
						//还原mat
						mat = newMat;
						if (fillMatrix(mat, transformGraph, unfill, int2char(i)))
						{//如果能够添加，mat已经被填充；否则mat没有被填充
							//PrintMatrix(mat);
							Counter++;
							used[i] = true;//该图形标记为使用
							dfs(sum + 1, used, mat, answer, StartGraphIdx, Counter);//进行下一次的DFS
							used[i] = false;//把图形标记为未使用，供下次深度搜索
						}
					}
				}
				//还原mat
				mat = newMat;

			}
		}
	}
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