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
using namespace std;
struct student{
	int c, m, e, rank;
	int a;
	string course, ID;
	int tmpRank;//用来存在不同状态下的排名，主要是更新并列排名
	student() :c(0), m(0), e(0), a(0), rank(9999999), tmpRank(9999999), course(""), ID(""){};
};
bool cmpC(const student&a, const student&b)
{
	if (a.c > b.c) return true;
	else return false;
}
bool cmpM(const student&a, const student&b)
{
	if (a.m > b.m) return true;
	else return false;
}
bool cmpE(const student&a, const student&b)
{
	if (a.e > b.e) return true;
	else return false;
}
bool cmpA(const student&a, const student&b)
{
	if (a.a > b.a) return true;
	else return false;
}
int main(void) {

	int n, m;
	cin >> n >> m;
	vector<student> stu(n);
	for (int i = 0; i < n; i++)
	{
		cin >> stu[i].ID >> stu[i].c >> stu[i].m >> stu[i].e;
		stu[i].a = (stu[i].c + stu[i].m + stu[i].e);
		stu[i].course = "";
		stu[i].rank = 9999999;
	}
	//比较平均分
	sort(stu.begin(), stu.end(), cmpA);
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
			stu[i].tmpRank = 0;
		else if (stu[i].a == stu[i - 1].a)
			stu[i].tmpRank = stu[i - 1].tmpRank;//如果分数相同，则排名相同
		else
			stu[i].tmpRank = i;//分数不同，则是i，例如 100 90 90 80 ，排名应该为1，2，2，4
		if (stu[i].rank > stu[i].tmpRank + 1)
		{
			stu[i].rank = stu[i].tmpRank + 1;
			stu[i].course = "A";
		}
	}
	//比较C语言
	sort(stu.begin(), stu.end(), cmpC);
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
			stu[i].tmpRank = 0;
		else if (stu[i].c == stu[i - 1].c)
			stu[i].tmpRank = stu[i - 1].tmpRank;//如果分数相同，则排名相同
		else
			stu[i].tmpRank = i;//分数不同，则是i，例如 100 90 90 80 ，排名应该为1，2，2，4
		if (stu[i].rank > stu[i].tmpRank + 1)
		{
			stu[i].rank = stu[i].tmpRank + 1;
			stu[i].course = "C";
		}
	}
	//比较Mathematics
	sort(stu.begin(), stu.end(), cmpM);
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
			stu[i].tmpRank = 0;
		else if (stu[i].m == stu[i - 1].m)
			stu[i].tmpRank = stu[i - 1].tmpRank;//如果分数相同，则排名相同
		else
			stu[i].tmpRank = i;//分数不同，则是i，例如 100 90 90 80 ，排名应该为1，2，2，4
		if (stu[i].rank > stu[i].tmpRank + 1)
		{
			stu[i].rank = stu[i].tmpRank + 1;
			stu[i].course = "M";
		}
	}
	//比较English
	sort(stu.begin(), stu.end(), cmpE);
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
			stu[i].tmpRank = 0;
		else if (stu[i].e == stu[i - 1].e)
			stu[i].tmpRank = stu[i - 1].tmpRank;//如果分数相同，则排名相同
		else
			stu[i].tmpRank = i;//分数不同，则是i，例如 100 90 90 80 ，排名应该为1，2，2，4
		if (stu[i].rank > stu[i].tmpRank + 1)
		{
			stu[i].rank = stu[i].tmpRank + 1;
			stu[i].course = "E";
		}
	}
	map<string, student> ma;
	for (int i = 0; i < n; i++)
	{
		ma[stu[i].ID] = stu[i];
	}

	for (int i = 0; i < m; i++)
	{
		string tmp;
		cin >> tmp;
		if (ma.find(tmp) == ma.end())
			cout << "N/A" << endl;
		else
			cout << ma[tmp].rank << " " << ma[tmp].course << endl;
	}
	return 0;
}