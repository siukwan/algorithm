/*
题目：
1.使用manacher算法进行检测，时间复杂度为O（n）
2.其中需要对字符串进行预处理，头部加上$，然后间隔加上#,如123变为$#1#2#3#
3.需要额外添加变量id，即最长回文的中心，mx，即最长回文的右边界
4.其中当mx>i，我们有定理p[i]>=min(p[j],mx-i)，其中j为i关于id的对称点，即j=2*id-i；即直接从p[i]进行检测
5.当mx<i时，无法进行更多的预测，需要从p[i]=1开始检测
6.检测完以当前字符串为中心的回文后，如果p[i]+i大于最长回文的右边界，则进行更新mx=p[i]=i,id=i;
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

int manacher(string str)
{
	vector<int > p(str.size(), 0);
	int id = 1;//初始化开始检测回文的中心为1
	int mx = 0;//初始化最大的边界值为0
	for (int i = 1; i < str.size(); i++)
	{
		//如果边界值mx大于i，那么p[i] = min(p[2 * id - i], mx - i);
		if (mx > i)
			p[i] = min(p[2 * id - i], mx - i);
		//否则，无法对p[i]进行预测，令p[i]=1
		else
			p[i] = 1;
		//检测回文
		while (str[i + p[i]] == str[i - p[i]])
			p[i]++;
		//如果大于最大边界，则进行更新
		if (p[i] + i > mx)
		{
			mx = p[i] + i;
			id = i;
		}
	}
	int maxP = INT_MIN;
	for (int i = 0; i < p.size(); i++)
		maxP = max(p[i], maxP);
	return maxP - 1;
}
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int n;
	scanf("%d", &n);
	while (n--)
	{
		string str;
		cin >> str;
		string newStr = "$#";
		for (int i = 0; i < str.size(); i++)
		{
			newStr += str[i];
			newStr += '#';
		}
		cout << manacher(newStr) << endl;
	}
	return  0;
}