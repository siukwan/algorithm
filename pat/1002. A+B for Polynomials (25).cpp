//#include<string>
//#include<stack>
//#include<unordered_set>
//#include <sstream>
//#include "func.h"
//#include <list>
#include <iomanip>
#include<unordered_map>
#include<set>
#include<queue>
#include<map>
#include<vector>
#include <algorithm>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
#include<stack>
using namespace std;

int main(void)
{
	vector<float> N1(1002, 0);
	vector<float> N2(1002, 0);
	int n, m;
	cin >> n;
	//输入第一个多项式
	for (int i = 0; i < n; i++)
	{
		int idx = 0;
		cin >> idx;
		cin >> N1[idx];
	}

	cin >> m;
	//输入第二个多项式
	for (int i = 0; i < m; i++)
	{
		int idx = 0;
		cin >> idx;
		cin >> N2[idx];
	}

	//同阶的系数相加
	for (int i = 0; i < N1.size(); i++)
	{
		N1[i] = N1[i] + N2[i];
	}

	int sum = 0;
	for (int i = 0; i < N1.size(); i++)
	{
		if (N1[i] != 0)
			sum++;
	}
	cout << sum;
	for (int i = N1.size() - 1; i >= 0; i--)
	{//高位先输出
		if (N1[i] != 0)//不为0，则输出
			printf(" %d %.1f", i, N1[i]);
	}
	return 0;
}