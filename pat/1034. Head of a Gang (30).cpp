//#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
#include<set>
#include<queue>
#include<map>
//#include<unordered_set>
#include<unordered_map>
//#include <sstream>
//#include "func.h"
//#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
using namespace std;

struct guyNode{
	set<string> contact;
	int time;
	string r;
	guyNode() : time(0), r(""){ contact.clear(); };
};
string find(string a, map<string, guyNode>&m)
{
	if (m[a].r == a)
		return a;
	else
	{
		m[a].r = find(m[a].r, m);
		return m[a].r;
	}
}

int main(void)
{
	int recordNum, threshold;
	cin >> recordNum >> threshold;
	map<string, guyNode> m;//存储每个人的总通话时间和联系人
	for (int i = 0; i < recordNum; i++)
	{//输入联系记录
		string a, b;
		int time;
		cin >> a >> b >> time;
		if (m[a].r == "") m[a].r = a;//如果是第一次输入，则把代表设为自己
		if (m[b].r == "") m[b].r = b;
		m[a].contact.insert(b);//增加联系人b
		m[a].time += time;//累加通话时间
		m[b].contact.insert(a);//增加联系人a
		m[b].time += time;//累加通话时间
		if (find(a, m) != find(b, m))
			m[find(a, m)].r = find(b, m);//合并
	}

	map<string, set<string>> gang;//存储gang的代表和成员，注意，代表还不是头目
	map<string, int> contactTime;//计算各个gang的总通话时间，注意，a和b通话，a累加了一次时间，b又累加了一次时间，所以是实际时间的两倍
	for (map<string, guyNode>::iterator ite = m.begin(); ite != m.end(); ite++)
	{//遍历所有的集合
		gang[find(ite->first, m)].insert(ite->first);//利用并查集，分为不同的集合gang
		contactTime[find(ite->first, m)] += ite->second.time;//统计各个gang的时间
	}
	map<string, int> ans;
	for (map<string, set<string>>::iterator ite = gang.begin(); ite != gang.end(); ite++)
	{
		if (contactTime[ite->first] <= threshold * 2 || ite->second.size() <= 2)
			continue;//通话时间不满足要求,人数少于两人

		bool isGang = true;//标志位
		string head = "";//设置头目信息
		int maxTime = 0;//通话时间为0
		int sum = ite->second.size();//gang的总人数
		for (set<string>::iterator ite2 = ite->second.begin(); ite2 != ite->second.end(); ite2++)
		{
			string name = *ite2;
			if (m[name].time > maxTime)
			{//查找通话时间最长的人，即head of gang
				head = name;
				maxTime = m[name].time;
			}
		}
		if (isGang)
		{
			ans[head] = sum;
		}
	}
	cout << ans.size() << endl;
	for (map<string, int>::iterator ite = ans.begin(); ite != ans.end(); ite++)
	{//输出gang的head和成员数
		cout << ite->first << " " << ite->second << endl;
	}





	return 0;
}