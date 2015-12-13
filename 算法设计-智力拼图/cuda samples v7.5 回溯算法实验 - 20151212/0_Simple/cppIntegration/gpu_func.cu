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

#ifndef MAX
#define MAX(a,b) (a > b ? a : b)
#endif

////////////////////////////////////////////////////////////////////////////////
// declaration, forward
////////////////////////////////////////////////////////////////////////////////
/*记录单个图形的长宽和形状*/
struct GraphNode
{
	char shape[5][5];      //图形的形状，因为bool也占用了1B，所以使用char或者bool都可以
	int x;                //图形的高度
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


///////////////////////////////////////////////////////////////////////////////
//! Simple test kernel for device functionality
//! @param g_graph  memory to process (in and out)
///////////////////////////////////////////////////////////////////////////////
__global__ void gpuTestSiukwan(GraphAll *const g_graph)
{
	// write data to global memory
	const unsigned int tid = threadIdx.x;
	for (int k = 0; k < g_graph->graph[tid].formatCount; k++)
	{
		for (int i = 0; i < g_graph->graph[tid].format[k].x; i++)
		{
			for (int j = 0; j < g_graph->graph[tid].format[k].y; j++)
			{
				//g_graph->graph[tid].format[k].shape[i][j] += '0';
			}
		}
	}
}

extern "C" bool
SiukwanTest(GraphAll *const g_graph)
{
	gpuTestSiukwan << < 1, 12 >> >(g_graph);
	return true;
}




/*
函数名  ：getFirstUnfill
函数功能：检测矩阵mat中第一个空白的格子（坐标）
输入参数：
mat:检测的mat
*/
__device__ void getFirstUnfill(MatrixNode &g_mat, int &x, int&y)
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
函数名  ：getFirstFill
函数功能：检测graph中第一行有值的位置（坐标）
输入参数：
graph:检测的graph
*/
__device__ void getFirstFill(GraphNode &graph, int &x, int&y)
{
	for (int j = 0; j < graph.x; j++)
	{
		for (int h = 0; h < graph.y; h++)
		{//找出第一个未填的位置，记录下来，直接跳出
			if (graph.shape[j][h] != 0)
			{//不为0，即有值
				x = j;
				y = h;
				break;
			}
		}
		if (x != -1) break;
	}
}

/*
函数名  ：canFillMatrix
函数功能：图案能否填充到矩阵中
输入参数：
g_mat    :被填充的矩阵
graph    :用来填充的图形
toFill_x :被填充矩阵的第一个空格位置x
toFill_y :被填充矩阵的第一个空格位置y
fill_x   :填充的图形的第一个非空格位置x
fill_y   :填充的图形的第一个非空格位置y
*/
__device__ bool canFillMatrix(MatrixNode &g_mat, GraphNode &graph, int&toFill_x, int&toFill_y,  int&fill_x, int&fill_y)
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



__global__ void dfsCUDA_LastVersion(MatrixNode *const g_mat, GraphAll *const g_graph, int*solutionSum)
{
	// write data to global memory
	const unsigned int tid = (blockIdx.x*blockDim.x) + threadIdx.x;
	if (tid >= solutionSum[0]) return;

	//获取未填充的第一个空格
	int unfill_x = -1, unfill_y = -1;
	getFirstUnfill(g_mat[tid], unfill_x, unfill_y);

	//一开始只分12条线程，线程id即图形id
	if (g_mat[tid].depth == 0)
	{
		for (int j = 0; j < g_graph->graph[tid].formatCount; j++)
		{
			if (canFillMatrix(g_mat[tid], g_graph->graph[tid].format[j], unfill_x, unfill_y, g_graph->graph[tid].format[j].fill_x, g_graph->graph[tid].format[j].fill_y))
			{//记录i和j，记录下一次哪些答案可行
				//该层答案数增加
				g_mat[tid].thisLevelCount++;
				g_mat[tid].solution[tid][j] = true;//记录方案i，j可行
			}
		}
	}
	else
	{
		//遍历它下面的12个图形
		for (int i = 0; i < 12; i++)
		{
			if (g_mat[tid].graphUsed[i])
				continue;
			for (int j = 0; j < g_graph->graph[i].formatCount; j++)
			{
				if (canFillMatrix(g_mat[tid], g_graph->graph[i].format[j], unfill_x, unfill_y, g_graph->graph[i].format[j].fill_x, g_graph->graph[i].format[j].fill_y))
				{//记录i和j，记录下一次哪些答案可行
					//该层答案数增加
					g_mat[tid].thisLevelCount++;
					g_mat[tid].solution[i][j] = true;//记录方案i，j可行
				}
			}
		}
	}
	//层数++
	g_mat[tid].depth++;
}

//接口函数
extern "C" void runCUDA(int blocks, int threads, MatrixNode *const g_mat, GraphAll *const g_graph, int *solutionSum)
{
	dfsCUDA_LastVersion << < blocks, threads >> >(g_mat, g_graph, solutionSum);
}

