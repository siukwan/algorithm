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
/*
3
0011111
The Testing Book
Yue Chen
test code debug sort keywords

2011
3333333
Another Testing Book
Yue Chen
test code sort keywords
ZUCS Print2
2012
2222222
The Testing Book
CYLL
keywords debug book
ZUCS Print2
2011
6
1: The Testing Book
2: Yue Chen
3: keywords
4:
5: 2011
3: blablabla

*/
int str2int(string s)
{
	int a = 0;
	for (int i = 0; i < s.size(); i++)
	{
		a = s[i] - '0' + a * 10;
	}
	return a;
}
int main(void)
{
	string bookNumStr;
	getline(cin, bookNumStr);
	int bookNum;
	bookNum = str2int(bookNumStr);
	//最终查询输出的是ID，所以针对每个查询的词条，都建立一个ID集合
	//使用set存储ID，直接进行了排序
	map<string, set<string>> keyWord;//1000*80B+5*10000*7B=80K+350K=430K
	map<string, set<string>> publisher;//1000*80B+10000*7B=80K+70K=150K
	map<string, set<string>> year;//2000*4B+10000*7B=8K+70K=78K
	map<string, set<string>> author;//10000*80B+10000*7B=800K+70K=870K
	map<string, set<string>> title;//10000*80B+10000*7B=800K+70K=870K

	for (int i = 0; i < bookNum; i++)
	{
		string ID;
		string IDstr, titleTemp, authorTemp, keyWordTemp, publishedTemp, yearTemp;
		getline(cin, IDstr, '\n');

		getline(cin, titleTemp, '\n');
		getline(cin, authorTemp, '\n');
		getline(cin, keyWordTemp, '\n');
		getline(cin, publishedTemp, '\n');
		getline(cin, yearTemp, '\n');

		//ID = str2int(IDstr);
		ID = IDstr;

		int start = 0;
		for (int j = 0; j < keyWordTemp.size(); j++)
		{
			if (keyWordTemp[j] == ' ')
			{
				string temp = keyWordTemp.substr(start, j - start);
				start = j + 1;//跳过空格
				keyWord[temp].insert(ID);
			}
		}
		if (keyWordTemp.substr(start) != "")
			keyWord[keyWordTemp.substr(start)].insert(ID);
		if (titleTemp != "")
			title[titleTemp].insert(ID);
		if (authorTemp != "")
			author[authorTemp].insert(ID);
		if (publishedTemp != "")
			publisher[publishedTemp].insert(ID);
		if (yearTemp != "")
			year[yearTemp].insert(ID);
	}
	string queryStr;
	getline(cin, queryStr, '\n');
	int query = str2int(queryStr);
	for (int i = 0; i < query; i++)
	{
		string s;
		getline(cin, s, '\n');
		string outStr = s;
		int num;
		num = s[0] - '0';
		s = s.substr(3);
		cout << outStr << endl;
		if (num == 1 && title.find(s) != title.end())
		{//查询的是title
			for (set<string>::iterator ite = title[s].begin(); ite != title[s].end(); ite++)
				cout << *ite << endl;
		}
		else if (num == 2 && author.find(s) != author.end())
		{//查询的是作者
			for (set<string>::iterator ite = author[s].begin(); ite != author[s].end(); ite++)
				cout << *ite << endl;
		}
		else if (num == 3 && keyWord.find(s) != keyWord.end())
		{//查询的是关键词
			for (set<string>::iterator ite = keyWord[s].begin(); ite != keyWord[s].end(); ite++)
				cout << *ite << endl;
		}
		else if (num == 4 && publisher.find(s) != publisher.end())
		{//查询的是出版商
			for (set<string>::iterator ite = publisher[s].begin(); ite != publisher[s].end(); ite++)
				cout << *ite << endl;
		}
		else if (num == 5 && year.find(s) != year.end())
		{//查询的是年份
			for (set<string>::iterator ite = year[s].begin(); ite != year[s].end(); ite++)
				cout << *ite << endl;
		}
		else
		{//没有找到对应结果
			cout << "Not Found" << endl;
		}
	}
	return 0;
}