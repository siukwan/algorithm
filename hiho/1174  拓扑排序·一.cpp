/*
题目：
1.进行拓扑排序，比较简单。
*/
/*
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

struct CourseNode{
	bool visited;
	int degree;//入度
	vector<int> next;
	CourseNode() :visited(false),degree(0), next(0){};
};

/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{

	int t;
	cin >> t;
	while (t--)
	{
		int n, m;
		cin >> n >> m;
		//n门课程
		vector<CourseNode> course(n+1);

		for (int i = 0; i < m; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			course[a].next.push_back(b);
			course[b].degree++;
		}
		bool allOK = false;
		while (1)
		{
			bool change = false;
			allOK = true;
			for (int i = 1; i < course.size(); i++)
			{
				//搜索没有入度的节点
				if (!course[i].visited && course[i].degree == 0)
				{
					change = true;
					//把它的后置课程入度-1
					course[i].visited = true;
					for (int j = 0; j < course[i].next.size(); j++)
					{
						course[course[i].next[j]].degree--;
					}
				}
				else if (course[i].degree!=0)
					allOK = false;

			}
			//如果遍历一遍后没有改变，则退出循环
			if (!change) break;
		}
		if (allOK) printf("Correct\n");
		else printf("Wrong\n");
	}

	return  0;
}
