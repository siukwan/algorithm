/*
题目：

意思主要是从根到叶子节点，求出一个总和最大的路径的值。

主要使用动态规划，自底向上进行动态规划，每次挑选最大的值。
*/


#include<string>
#include <iomanip>
#include<fstream>
#include<set>
#include<queue>
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
using namespace std;
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	
	int n;
	scanf("%d", &n);
	int **reward = new int *[n];
	//输入数据
	for (int i = 0; i<n; i++)
	{
		reward[i] = new int[i + 1];
		for (int j = 0; j <= i; j++)
		{
			scanf("%d", &reward[i][j]);
		}
	}

	//自底向上，进行动态规划。
	for (int i = n - 2; i >= 0; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			reward[i][j] = reward[i][j] + max(reward[i + 1][j], reward[i + 1][j + 1]);
		}
	}
	printf("%d\n", reward[0][0]);
	return  0;
}
