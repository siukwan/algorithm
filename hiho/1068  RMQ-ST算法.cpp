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
using namespace std;

/*
这道题目主要是求解RMQ问题，给出某个查询的范围，求出该范围里面的最小值。

使用了ST算法，ST算法的详细说明为：http://siukwan.sinaapp.com/?p=830
*/

//stTable的准备函数
void ST_Prepare(vector<int> a, vector<vector<int>>&stTable)
{
	for (int i = a.size()-1; i >=0; i--)
	{
		//初始化0
		stTable[i][0] = a[i];
		//使用动态规划计算出stTable
		for (int j=1; i + (1<<j) -1 < a.size(); j++)
		{
			stTable[i][j] = min(stTable[i][j - 1], stTable[i + (1<<(j-1)) ][j - 1]);
		}
	}
}

int queryMin(int l, int r, vector<vector<int>>&stTable)
{
	int len = r - l + 1;
	int k = 0;
	int tmpLen = len;
	//求出合适的指数k
	while (tmpLen != 1)
	{
		k++;
		tmpLen = (tmpLen >> 1);
	}
	return min(stTable[l][k], stTable[r - (1 << k) + 1][k]);
}

/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int n;
	scanf("%d", &n);
	vector<int> a(n, 0);
	for (int i = 0; i < n;i++)
	{
		scanf("%d", &a[i]);
	}

	vector<vector<int>>stTable(n, vector<int>(32, 0));
	ST_Prepare(a, stTable);

	int queryN;
	scanf("%d", &queryN);
	while (queryN--)
	{
		int l, r;
		scanf("%d %d", &l, &r);
		int answer = queryMin(l-1, r-1, stTable);
		printf("%d\n", answer);
	}

	return  0;
}
