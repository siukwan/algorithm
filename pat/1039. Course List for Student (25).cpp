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
/*
ZOE1 2 4 5
ANN0 3 1 2 5
BOB5 5 1 2 3 4 5
JOE4 1 2
JAY9 4 1 2 4 5
FRA8 3 2 4 5
DON2 2 4 5
AMY7 1 5
KAT3 3 2 4 5
LOR6 4 1 2 4 5
NON9 0
*/
int main(void)
{

	int querySum, courseSum;
	cin >> querySum >> courseSum;
	vector<set<int>>stu(175761);//3个字母+1个数字，共26*26*26*10=175760种可能，直接开辟内存
	for (int i = 0; i<courseSum; i++)
	{
		int courseIdx, studentSum;
		scanf("%d %d", &courseIdx, &studentSum);
		for (int j = 0; j<studentSum; j++)
		{
			char tmp[5];
			scanf("%s", tmp);
			int name = (tmp[0] - 'A') * 26 * 26 * 10;
			name += (tmp[1] - 'A') * 26 * 10 + (tmp[2] - 'A') * 10 + tmp[3] - '0';
			stu[name].insert(courseIdx);
		}
	}

	for (int i = 0; i<querySum; i++)
	{
		char tmp[5];
		scanf("%s", tmp);
		int name = (tmp[0] - 'A') * 26 * 26 * 10;
		name += (tmp[1] - 'A') * 26 * 10 + (tmp[2] - 'A') * 10 + tmp[3] - '0';
		printf("%s %d", tmp, stu[name].size());
		for (set<int>::iterator ite = stu[name].begin(); ite != stu[name].end(); ite++)
		{
			printf(" %d", *ite);
		}
		cout << endl;
	}

	return 0;
}