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
int check;
struct studentNode{
	char id[7], name[8];
	int grade;
};
bool cmpID(const studentNode&a, const studentNode&b)
{
	return strcmp(a.id, b.id)<0;
}
bool cmpName(const studentNode&a, const studentNode&b)
{
	if (strcmp(a.name, b.name)<0) return true;
	else if (strcmp(a.name, b.name) == 0 && strcmp(a.id, b.id)<0) return true;
	else return false;
}
bool cmpGrade(const studentNode&a, const studentNode&b)
{
	if (a.grade < b.grade) return true;
	else if (a.grade == b.grade && strcmp(a.id, b.id)<0) return true;
	else return false;
}
bool cmp(const studentNode&a, const studentNode&b)
{
	if (check == 1)
		return cmpID(a, b);
	else if (check == 2)
		return cmpName(a, b);
	else return cmpGrade(a, b);
}

int main(void)
{
	int studentSum;
	cin >> studentSum >> check;
	studentNode *student = new studentNode[studentSum];
	for (int i = 0; i < studentSum; i++)
	{//scanf 输入char
		scanf("%s %s %d", &student[i].id, student[i].name, &student[i].grade);
	}
	sort(student, student + studentSum, cmp);
	for (int i = 0; i < studentSum; i++)
	{
		printf("%s %s %d\n", student[i].id, student[i].name, student[i].grade);
	}
	return 0;
}