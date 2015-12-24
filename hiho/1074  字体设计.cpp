/*
题目：
实则为RMQ问题。

主要求出锚点，锚点即为包含区间的两端，包含区间里面的数统一大于起点，且小于终点；或者统一小于起点，且大于重点。

使用ST表进行求解，其中我们需要求出两个ST表，一个用来存储最大值的，一个用来存储最小值的。

我们通过不断递归搜索区间[l,r]，找出区间中的最大值maxPos和最小值minPos的位置，然后划分为三个区间：
如果maxPos>minPos，则三个区间为：
[l,minPos],[minPos,maxPos],[maxPos,r]

如果maxPos<minPos，则三个区间为：
[l,maxPos],[maxPos,minPos],[minPos,r]

然后挑选出锚点
*/


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

vector<int> preLog2;
//预先计算log2数组，方便后续处理
void calPreLog2(int n,vector<int>&log2)
{
	log2[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		log2[i] = log2[i - 1];
		//恰好是2的次方
		if ((1 << (log2[i] + 1)) == i)
			log2[i]++;
	}
}
vector<int> arr;
vector<vector<pair<int, int>>> stMin;
vector<vector<pair<int, int>>> stMax;

//准备st表
void ST_Prepare()
{
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		stMin[i][0] = { arr[i], i };
		stMax[i][0] = { arr[i], i };
		for (int j = 1; i + (1 << j) - 1 < arr.size(); j++)
		{
			//求min
			if (stMin[i][j - 1].first < stMin[i + (1 << (j - 1))][j - 1].first)
				stMin[i][j] = stMin[i][j - 1];
			else
				stMin[i][j] = stMin[i + (1 << (j - 1))][j - 1];

			//求max
			if (stMax[i][j - 1].first > stMax[i + (1 << (j - 1))][j - 1].first)
				stMax[i][j] = stMax[i][j - 1];
			else
				stMax[i][j] = stMax[i + (1 << (j - 1))][j - 1];
		}
	}
}
//查询最小值
int queryMin(int l, int r)
{
	int len = r - l + 1;
	int k = preLog2[len];
	if (stMin[l][k].first < stMin[r - (1 << k) + 1][k].first)
		return stMin[l][k].second;
	else
		return stMin[r - (1 << k) + 1][k].second;
}
//查询最大值
int queryMax(int l, int r)
{
	int len = r - l + 1;
	int k = preLog2[len];
	if (stMax[l][k].first > stMax[r - (1 << k) + 1][k].first)
		return stMax[l][k].second;
	else
		return stMax[r - (1 << k) + 1][k].second;
}
map<int,int> ans;

//递归找出包含区间，这些区间的特点是起点和终点分别是最大值和最小值（或最小值和最大值）
void dfs(int l,int r)
{
	//求出最大值最小值的位置
	int minPos = queryMin(l, r);
	int maxPos = queryMax(l, r);
	if (l == r)
	{//如果左右相等，则压入答案后直接返回
		ans[l]=1;
		return;
	}
	//如果最大值和最小值恰好是区间的两端，则压入答案后直接返回
	else if ((l == minPos&&r == maxPos) || (l == maxPos &&r == minPos))
	{
		ans[l] = 1;
		ans[r] = 1;
		return;
	}

	//进行递归
	dfs(l, min(minPos, maxPos));
	dfs(min(minPos, maxPos), max(minPos, maxPos));
	dfs(max(minPos, maxPos), r);
}

/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int n;
	scanf("%d", &n);
	arr = vector<int>(n, 0);
	for (int i = 0; i < n;i++)
	{
		scanf("%d", &arr[i]);
	}

	preLog2 = vector<int>(n+1, 0);
	stMin = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(32, { 0, 0 }));
	stMax = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(32, { 0, 0 }));

	//预处理求出log2，log2向下取整
	calPreLog2(n, preLog2);
	//预处理stTable，包括最大值和最小值
	ST_Prepare();
	//进行递归搜索
	dfs(0, n - 1);

	printf("%d\n", ans.size());
	for (map<int, int>::iterator ite = ans.begin(); ite != ans.end(); ite++)
	{
		printf("%d ", ite->first + 1);
	}
	printf("\n");
	return  0;
}
