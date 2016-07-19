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

int main(void)
{
	int studentSum, courseSum;
	scanf("%d %d", &studentSum, &courseSum);
	char name[5];
	vector<vector<int>> course(courseSum);
	int *courseIdx = new int[20];
	int nameInt;
	int chooseSum;
	for (int i = 0; i<studentSum; i++)
	{//输入学生即其所选的课程
		scanf("%s", name);
		nameInt = (name[0] - 'A') * 26 * 26 * 10 + (name[1] - 'A') * 26 * 10 + (name[2] - 'A') * 10 + (name[3] - '0');
		scanf("%d", &chooseSum);
		for (int j = 0; j<chooseSum; j++)
		{
			scanf("%d", &courseIdx[j]);
			course[courseIdx[j] - 1].push_back(nameInt);
		}
	}
	for (int i = 0; i<course.size(); i++)
	{//输出各门课程的结果
		printf("%d %d\n", i + 1, course[i].size());
		sort(course[i].begin(), course[i].end());
		for (vector<int>::iterator ite = course[i].begin(); ite != course[i].end(); ite++)
		{//转化学生的名字，进行输出
			name[4] = 0;
			name[3] = (*ite) % 10 + '0';
			name[2] = ((*ite) / 10) % 26 + 'A';
			name[1] = ((*ite) / 10 / 26) % 26 + 'A';
			name[0] = ((*ite) / 10 / 26 / 26) + 'A';
			printf("%s\n", name);
		}
	}

	return 0;
}