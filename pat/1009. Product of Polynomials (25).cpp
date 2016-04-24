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
using namespace std;
int main(void) {

	int n, m;
	cin >> n;
	vector<double> NK1(1001, 0);
	vector<double> NK2(1001, 0);
	vector<double> NK(1000001, 0);//直接创建1000*1000+1的数组
	//输入第一个多项式
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		cin >> NK1[temp];
	}

	cin >> m;
	//输入第二个多项式
	for (int i = 0; i < m; i++)
	{
		int temp;
		cin >> temp;
		cin >> NK2[temp];
	}
	//进行相乘
	for (int i = 0; i < 1001; i++)
	{
		for (int j = 0; j < 1001; j++)
		{
			if (NK1[i] != 0 && NK2[j] != 0)
			{
				NK[i + j] += NK1[i] * NK2[j];
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < 1000001; i++)
	{//统计有多少项非零
		if (NK[i] != 0) sum++;
	}
	cout << sum;
	if (sum != 0) cout << " ";
	for (int i = 1000000; i >= 0; i--)
	{
		if (NK[i] != 0)
		{//输出非零的多项式
			printf("%d %.1lf", i, NK[i]);
			sum--;
			if (sum != 0) cout << " ";
		}

	}
	return 0;
}