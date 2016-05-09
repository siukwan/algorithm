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
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85

2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
1
1234567890013 65

2
5
1234567890005 100
1234567890003 95
0000567890001 95
1234567890002 77
1234567890004 85
0

*/
struct studentNode{
	string id;
	int location, finalRank, localRank, score;
	studentNode() :id(""), location(-1), finalRank(-1), localRank(-1), score(-1){};
	studentNode(string i, int s) :id(i), location(-1), finalRank(-1), localRank(-1), score(s){};
};
bool cmp(const studentNode& a, const studentNode&b)
{
	if (a.score > b.score)
		return true;
	else if (a.score == b.score&&a.id < b.id)//分数相等的，ID按照递增排列
		return true;
	else return false;
}
int main(void)
{
	vector<studentNode> student(0);
	int locationNum, studentNum = 0;
	cin >> locationNum;//输入排名表的个数
	for (int location = 0; location < locationNum; location++)
	{
		int testNum; cin >> testNum;//输入每个排名表的学生数量
		if (testNum > 0)
		{
			for (int i = 0; i < testNum; i++)
			{
				string id; int score;
				cin >> id >> score;
				student.push_back(studentNode(id, score));
				student.back().location = location + 1;
				studentNum++;
			}

			//对排名表区域内的学生进行排序
			sort(student.begin() + studentNum - testNum, student.begin() + studentNum, cmp);
			student[studentNum - testNum].localRank = 1;
			for (int i = studentNum - testNum + 1; i < studentNum; i++)
			{//处理排名，相同分数的学生，排名相同。如100，90，90，80，排名为1，2，2，4
				if (student[i].score == student[i - 1].score)
					student[i].localRank = student[i - 1].localRank;
				else
					student[i].localRank = i - (studentNum - testNum) + 1;
			}
		}
	}
	if (studentNum > 0)
	{//如果学生数量大于0，进行排序和统计排名
		sort(student.begin(), student.end(), cmp);
		student[0].finalRank = 1;
		for (int i = 1; i < studentNum; i++)
		{
			if (student[i].score == student[i - 1].score)
				student[i].finalRank = student[i - 1].finalRank;
			else
				student[i].finalRank = i + 1;
		}
	}
	cout << studentNum << endl;
	for (int i = 0; i < studentNum; i++)
	{
		cout << student[i].id << " " << student[i].finalRank << " " << student[i].location << " " << student[i].localRank << endl;
	}
	return 0;
}