////////////////////////////////////////////////////////////////////////////
//
// Copyright 1993-2015 NVIDIA Corporation.  All rights reserved.
//
// Please refer to the NVIDIA end user license agreement (EULA) associated
// with this source code for terms and conditions that govern your use of
// this software. Any use, reproduction, disclosure, or distribution of
// this software and related documentation outside the terms of the EULA
// is strictly prohibited.
//
////////////////////////////////////////////////////////////////////////////

/*
* 关于智力拼图问题的GPU解法
*/

// System includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

// CUDA runtime
#include <cuda_runtime.h>

// helper functions and utilities to work with CUDA
#include <helper_cuda.h>
#include <helper_functions.h>

/*
函数名  ：addOne
函数功能：进行+1操作
输入参数：
num      :需要加1的数
*/
__device__ void addOne(int &num)
{
	num++;
}
/*
函数名  ：gpuTestSiukwanAddOne
函数功能：计算a_gpu[i] * b_gpu[i]，并把结果存放到c_gpu[i]中，实现设备端的函数调用
输入参数：
a_gpu    :被填充的矩阵
b_gpu    :用来填充的图形
c_gpu    :被填充矩阵的第一个空格位置x
*/
__global__ void gpuTestSiukwanAddOne(int *const a_gpu, int *const b_gpu, int *const c_gpu)
{
	// write data to global memory
	const unsigned int tid = (blockIdx.x*blockDim.x) + threadIdx.x;
	c_gpu[tid] = a_gpu[tid] * b_gpu[tid];
	for (int i = 0; i < 10240; i++)
		addOne(c_gpu[tid]);
}

/*
函数名  ：gpuTestSiukwan
函数功能：计算a_gpu[i] * b_gpu[i]，并把结果存放到c_gpu[i]中,
输入参数：
a_gpu    :被填充的矩阵
b_gpu    :用来填充的图形
c_gpu    :被填充矩阵的第一个空格位置x
*/
__global__ void gpuTestSiukwan(int *const a_gpu, int *const b_gpu, int *const c_gpu)
{
	// write data to global memory
	const unsigned int tid = (blockIdx.x*blockDim.x) + threadIdx.x;
	c_gpu[tid] = a_gpu[tid] * b_gpu[tid];
	for (int i = 0; i < 10240; i++)
		c_gpu[tid]++;
}

//接口函数
extern "C" void runCUDA(int blocks, int threads, int *const a_gpu, int *const b_gpu, int *const c_gpu)
{
	gpuTestSiukwan << < blocks, threads >> >(a_gpu, b_gpu, c_gpu);
}

//接口函数
extern "C" void runCUDA_AddOne(int blocks, int threads, int *const a_gpu, int *const b_gpu, int *const c_gpu)
{
	gpuTestSiukwanAddOne << < blocks, threads >> >(a_gpu, b_gpu, c_gpu);
}