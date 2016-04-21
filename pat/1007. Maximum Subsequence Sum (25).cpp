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

	int n;
	cin >> n;
	if (n == 0)
	{
		cout << "0 0 0" << endl;
		return 0;
	}
	long long *num = new long long[n];
	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
	}
	//使用pair，first代表从那个i开始，second表示从i加到当前数字的综合
	vector<pair<int, long long>> dp(n, { 0, 0 });
	dp[0].first = 0;
	dp[0].second = num[0];
	bool negative = true;
	if (num[0] >= 0) negative = false;//注意第一个数也要判断正负
	for (int i = 1; i < n; i++)
	{
		if (negative&&num[i] >= 0) negative = false;//判断是否全负数
		if (dp[i - 1].second <= 0)
		{//如果dp[i-1]小于0，那么num[i]加上它肯定小于num[i]，所以不加
			dp[i].first = i;
			dp[i].second = num[i];
		}
		else
		{//如果dp[i-1]大于等于0，那么num[i]加上它肯定大于等于num[i]，所以需要加上
			dp[i].first = dp[i - 1].first;
			dp[i].second = dp[i - 1].second + num[i];
		}

	}

	if (negative)
	{//如果全为负数，则输出首尾两个数
		cout << 0 << " " << num[0] << " " << num[n - 1] << endl;
	}
	else
	{
		long long maxAns = -1; int index = -1;
		for (int i = 0; i < n; i++)
		{//遍历一遍，找出second最大的dp
			if (maxAns < dp[i].second)
			{
				maxAns = dp[i].second;
				index = i;
			}
		}
		//根据题目要求输出最大的和，和相当一序列起始值和结束值
		cout << dp[index].second << " " << num[dp[index].first] << " " << num[index] << endl;
	}

	return 0;
}