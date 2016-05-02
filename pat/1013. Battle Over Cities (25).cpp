//#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
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
/*
1 0 1
1
输出 0

*/
using namespace std;
struct edgeNode{
	int a, b;
	edgeNode() :a(0), b(0){};
};
int find(int k, vector<int>&r)
{
	if (r[k] == k)
		return r[k];
	else
	{
		r[k] = find(r[k], r);
		return r[k];
	}
}
int main(void) {

	int n, m, k;
	cin >> n >> m >> k;
	n++;//城市从1开始，方便操作
	vector<vector<bool>> w(n, vector<bool>(n, false));//使用邻接矩阵存储，避免超时超内存，之前使用edge存储，结果段错误（超内存了）
	for (int i = 0; i < m; i++)
	{//输入边
		int a, b;
		cin >> a >> b;
		w[a][b] = true;
		w[b][a] = true;
	}
	for (int i = 0; i < k; i++)
	{
		int city;
		cin >> city;
		static vector<int> r(n, 0);
		for (int i = 0; i < n; i++)
			r[i] = i;
		//r[city] = 10000;
		for (int i = 1; i < n; i++)
		{
			if (i == city) continue;
			for (int j = i; j < n; j++)
			{
				if (j == city) continue;
				if (w[i][j])
					r[find(j, r)] = find(i, r);//否则合并两个城市
			}
		}
		int sum = -2;
		for (int i = 1; i < n; i++)
			if (r[i] == i) sum++;

		//如果只有1个城市，则不用修路了
		if (n - 1 == 1)
			sum = 0;
		cout << sum << endl;
	}


	return 0;
}