/*
题目：
实则为RMQ问题。
主要使用线段树求解。
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

const int MAX_N = 1 << 20;
int SegTree[2 * MAX_N - 1];
int n;
void init(int size)
{
	n = 1;
	//把线段树的大小扩充到2的n次方
	while (n < size) n *= 2;
	//初始化为最大值
	for (int i = 0; i < 2 * n - 1; i++)
		SegTree[i] = INT_MAX;
}

void update(int k, int val)
{
	//前面n-1个节点用来存储非叶子节点的线段树节点
	//最后的n个节点是用来存储数组
	k += n - 1;
	SegTree[k] = val;
	while (k > 0)
	{
		//找到父节点
		k = (k - 1) / 2;
		//取左右儿子的最大值
		SegTree[k] = min(SegTree[k * 2 + 1], SegTree[k * 2 + 2]);
	}
}

int query(int a, int b, int k, int l, int r)
{

	//如果[a,b)与[l,r)不相交
	if (r <= a || b <= l) return INT_MAX;

	//如果[a,b)包含[l,r），则返回当前节点的值
	if (a <= l && r <= b || k>n) return SegTree[k];
	else
	{//把区间分成两部分进行查询
		int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return min(vl, vr);
	}

}

/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int sum;
	scanf("%d", &sum);
	init(sum);
	for (int i = 0; i < sum; i++)
	{
		int tmp;
		scanf("%d", &tmp);
		//初始化的时候使用update操作
		update(i, tmp);
	}
	int queryN;
	scanf("%d", &queryN);
	while (queryN--)
	{
		int operation, a, b;
		scanf("%d %d %d", &operation, &a, &b);
		if (operation == 0)
		{
			//因为查询求解的是[a,b)区间，需要注意
			printf("%d\n", query(a - 1, b, 0, 0, n));
		}
		else
		{
			update(a - 1, b);
		}
	}

	return  0;
}