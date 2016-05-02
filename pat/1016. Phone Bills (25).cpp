/*
1.判断记录好坏，把所有记录以string存起来，按照字典序排序，相邻的两条记录满足要求：第一条为on-line且第二条为off-line,才是成功匹配；
2.采用计算00:00:00到现在的耗费和分钟数，这个方法比较简单
3.最重要的：题目中只强调至少有一条匹配成功的记录，不是说每个人都至少有一条匹配成功的记录，所以没有成功匹配记录的人不输出（主要卡在这）
*/
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
struct customNode{
	string month;
	vector<string> online;
	vector<string> offline;
	vector<pair<string, string>> recordTag;
	vector<pair<string, string>> pairRecord;
	vector<pair<int, int>> eachCost;
	int total;
	customNode() :month(""), online(0), offline(0), eachCost(0), total(0){};
};
int str2int(string a){ return (a[0] - '0') * 10 + a[1] - '0'; }

int calculateCostFromZero(string a, vector<int>& rate)
{//计算从00:00:00到某个时间的耗费
	int rateSum = 0;//一天的总和
	for (int i = 0; i < 24; i++)
	{
		rateSum += rate[i] * 60;
	}
	int day = str2int(a.substr(3, 2));//天数
	int hour = str2int(a.substr(6, 2));//小时数
	int minute = str2int(a.substr(9, 2));//小时数
	int totalCost = day*rateSum;
	totalCost += minute*rate[hour];

	for (int i = 0; i < hour; i++)
	{
		totalCost += rate[i] * 60;
	}
	return totalCost;
}
int calculateMinutesFromZero(string a)
{//计算从00:00:00到某个时间的分钟数
	int day = str2int(a.substr(3, 2));//天数
	int hour = str2int(a.substr(6, 2));//小时数
	int minute = str2int(a.substr(9, 2));//小时数
	return day * 1440 + hour * 60 + minute;
}

pair<int, int> calculate(string a, string b, vector<int>& rate)
{//分别计算00:00:00和当前日期的差值

	int startCost = calculateCostFromZero(a, rate);
	int endCost = calculateCostFromZero(b, rate);
	int startMin = calculateMinutesFromZero(a);
	int endMin = calculateMinutesFromZero(b);

	return{ endCost - startCost, endMin - startMin };

}

pair<int, int> calculate2(string a, string b, vector<int>& rate)
{//计算差值的方法不是很好
	int startHour = str2int(a.substr(6, 2));//计算开始所在的小时
	int endHour = str2int(b.substr(6, 2));//计算结束时所在的小时
	int startNoDay = startHour * 60 + str2int(a.substr(9, 2));//计算H*60+m，单位为分钟
	int endNoDay = endHour * 60 + str2int(b.substr(9, 2));//计算H*60+m，单位为分钟

	int startWithDay = str2int(a.substr(3, 2)) * 1440 + startNoDay;//加上天数，单位为分钟
	int endWithDay = str2int(b.substr(3, 2)) * 1440 + endNoDay;//加上天数，单位为分钟
	int days = (endWithDay - startWithDay) / 1440;//查看隔了多少天
	int total = 0;
	for (int j = 0; j < days; j++)
	{//每多一天，都需要加上24小时的计费
		for (int i = 0; i < 24; i++)
			total += 60 * rate[i];
	}
	int recent = startNoDay;
	if (startNoDay > endNoDay)
	{
		endHour += 24;//如果起始的分钟数大于结束的分钟数，结束在第一天之后（有可能是2，3，4天），直接+24，便于统计
		endNoDay += 24 * 60;//No也需要加上24*60
	}
	for (int i = startHour + 1; i <= endHour && endHour != startHour; ++i)
	{//开始统计
		total += (i * 60 - recent)*rate[i - 1];
		recent = i * 60;
	}
	total += (endNoDay - recent)*rate[endHour];
	int diff = endWithDay - startWithDay;
	return{ total, diff };

}
bool cmpRecordTag(const pair<string, string>&a, const pair<string, string>&b)
{
	return a.first < b.first;
}
int main(void)
{

	vector<int> rate(48);// = { 10, 10, 10, 10, 10, 10, 20, 20, 20, 15, 15, 15, 15, 15, 15, 15, 20, 30, 20, 15, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 20, 20, 20, 15, 15, 15, 15, 15, 15, 15, 20, 30, 20, 15, 15, 10, 10, 10 };
	//int rateSum = 0;
	//for (int i = 0; i < 24; i++)
	//{
	//  rateSum += rate[i]*60;
	//}
	//vector<pair<int, int>> temp(0);
	//temp.push_back(calculate("01:28:23:41", "01:28:23:42", rate));
	//temp.push_back(calculate("01:28:15:41", "01:28:16:05", rate));
	//temp.push_back(calculate("01:01:05:59", "01:01:07:00", rate));
	//temp.push_back(calculate("01:02:00:01", "01:04:23:59", rate));
	//temp.push_back(calculate("01:01:06:01", "01:01:08:03", rate));
	//
	for (int i = 0; i < 24; i++)
	{
		scanf("%d", &rate[i]);
		rate[i + 24] = rate[i];
	}
	int recordNum;
	cin >> recordNum;
	map<string, customNode> m;
	vector<string> nameList(0);
	for (int i = 0; i < recordNum; i++)
	{//输入各条记录
		string name, time, tag;
		cin >> name >> time >> tag;
		if (m.find(name) == m.end())
			nameList.push_back(name);

		m[name].recordTag.push_back({ time, tag });
	}

	//直接sort，则string就是按照字典序进行排列
	sort(nameList.begin(), nameList.end());

	for (int i = 0; i < nameList.size(); i++)
	{
		string name = nameList[i];
		sort(m[name].recordTag.begin(), m[name].recordTag.end(), cmpRecordTag);
		m[name].total = 0;
		for (int j = 0; j + 1< m[name].recordTag.size(); j++)
		{
			if (m[name].recordTag[j].second == "on-line"&&m[name].recordTag[j + 1].second == "off-line")
			{//当前记录为on-line，且下一条为off-line，则匹配成功
				m[name].pairRecord.push_back({ m[name].recordTag[j].first.substr(3), m[name].recordTag[j + 1].first.substr(3) });
				m[name].eachCost.push_back(calculate(m[name].recordTag[j].first, m[name].recordTag[j + 1].first, rate));
				m[name].total += m[name].eachCost.back().first;
			}
		}
		if (m[name].pairRecord.size() != 0)
		{//题目只确保至少有一条成功匹配的记录，但是没有说每个人至少有一条成功匹配的记录
			//没成功匹配记录的人就不输出
			cout << name << " " << m[name].recordTag[0].first.substr(0, 2) << endl;
			for (int j = 0; j < m[name].pairRecord.size(); j++)
			{
				cout << m[name].pairRecord[j].first << " " << m[name].pairRecord[j].second << " " << m[name].eachCost[j].second << " $";
				printf("%.2f", m[name].eachCost[j].first / 100.0);
				cout << endl;
			}
			printf("Total amount: $%.2f", m[name].total / 100.0);
			cout << endl;
		}

	}


	return 0;
}