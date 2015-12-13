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


void initCUDAandShowMessage();
extern "C" void runCUDA(int blocks, int threads, int *const a_gpu, int *const b_gpu, int *const c_gpu);
extern "C" void runCUDA_AddOne(int blocks, int threads, int *const a_gpu, int *const b_gpu, int *const c_gpu);

void multipleCPU(int *const a_gpu, int *const b_gpu, int *const c_gpu)
{
	for (int i = 0; i < 1024*1024; i++)
	{
		c_gpu[i] = a_gpu[i] * b_gpu[i];
		for (int j = 0; j < 10240; j++)
			c_gpu[i]++;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	//显示显卡的相关信息
	initCUDAandShowMessage();



	//开启的线程块数量
	int blocks = 1;

	//每个线程块开启的线程数量
	int threads = 1024;

	//定义数组a，b，c，并初始化
	int *a_cpu = new int[1024 * 1024];
	int *b_cpu = new int[1024 * 1024];
	int *c_cpu = new int[1024 * 1024];
	for (int i = 0; i < 1024 * 1024; i++)
	{
		a_cpu[i] = 100;
		b_cpu[i] = 300;
		c_cpu[i] = 0;
	}

	//定义gpu上的变量
	int *a_gpu, *b_gpu, *c_gpu;

	//在gpu上分配内存
	cudaMalloc((void **)&a_gpu, sizeof(int) * 1024);
	cudaMalloc((void **)&b_gpu, sizeof(int) * 1024);
	cudaMalloc((void **)&c_gpu, sizeof(int) * 1024);

	//把数据从内存复制到显存
	cudaMemcpy(a_gpu, a_cpu, sizeof(int) * 1024, cudaMemcpyHostToDevice);
	cudaMemcpy(b_gpu, b_cpu, sizeof(int) * 1024, cudaMemcpyHostToDevice);



	//windows运行进行时间统计
	time_t  StartTime;
	time_t  EndTime;
	double  TimeUse = 0;
	time(&StartTime);


	//////////////////////////////////////////////////////
	//CUDA运算
	//////////////////////////////////////////////////////
	runCUDA(blocks, threads,a_gpu, b_gpu, c_gpu);


	//windows运行进行时间统计
	time(&EndTime);
	TimeUse = difftime(EndTime, StartTime);

	//把在gpu中处理完毕的数据从显存复制到内存
	cudaMemcpy(c_cpu, c_gpu, sizeof(int) * 1024, cudaMemcpyDeviceToHost);
	

	//释放相关变量的显存
	cudaFree(a_gpu);
	cudaFree(b_gpu);
	cudaFree(c_gpu);

	cout << "GPU总花费时间为：" << (int)TimeUse / 60 << "分" << ((int)TimeUse) % 60 << "秒" << endl;
	for (int i = 0; i < 1024; i+=200)
	{
		printf("c_cpu[%d]=%d\n",i, c_cpu[i]);
	}



	//////////////////////////////////////////////////////
	//CPU运算
	//////////////////////////////////////////////////////

	//windows运行进行时间统计
	time(&StartTime);
	multipleCPU(a_cpu, b_cpu, c_cpu);
	//windows运行进行时间统计
	time(&EndTime);
	TimeUse = difftime(EndTime, StartTime);
	cout << "CPU总花费时间为：" << (int)TimeUse / 60 << "分" << ((int)TimeUse) % 60 << "秒" << endl;
	for (int i = 0; i < 1024; i += 200)
	{
		printf("c_cpu[%d]=%d\n", i, c_cpu[i]);
	}

	//释放内存
	free(a_cpu);
	free(b_cpu);
	free(c_cpu);



    // cudaDeviceReset causes the driver to clean up all state. While
    // not mandatory in normal operation, it is good practice.  It is also
    // needed to ensure correct operation when the application is being
    // profiled. Calling cudaDeviceReset causes all profile data to be
    // flushed before the application exits
    cudaDeviceReset();
    exit(1);
}

/*
函数名  ：initCUDAandShowMessage
函数功能：读取显卡信息并进行输出
*/
void initCUDAandShowMessage()
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
}
