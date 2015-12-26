/*
题目：
1.把题目根据要求转化为拓扑排序求解。
2.首先遍历入度为0的节点，并把节点的病毒传递到其下一层的节点。
3.重复进行拓扑排序。
4.注意题目要求mod 142857
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

struct vertex{
	unsigned long long virus;
	int degree;
	bool visited;
	vector<int> next;
	vertex() :virus(0), degree(0), visited(false), next(0){};
};

/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int n, m, k;
	cin >> n >> m >> k;

	//节点个数
	vector<vertex> v(n + 1);

	//感染病毒的节点
	for (int i = 0; i < k; i++)
	{
		int tmp;
		scanf("%d", &tmp);
		v[tmp].virus = 1;
	}

	//输入边关系
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		v[a].next.push_back(b);
		v[b].degree++;
	}


	while (1)
	{
		bool change = false;
		for (int i = 1; i < v.size(); i++)
		{
			if (!v[i].visited && v[i].degree == 0)
			{
				change = true;
				v[i].visited = true;
				//需要MOD，避免后面溢出
				v[i].virus %= 142857;
				for (int j = 0; j < v[i].next.size(); j++)
				{
					//更新病毒和入度
					int l = v[i].next[j];
					v[l].degree--;
					v[l].virus += v[i].virus;
				}
			}
		}
		//如果没有变化，证明没有入度为0的节点了。
		if (!change) break;
	}

	unsigned long long  totalVirus = 0;
	for (int i = 1; i < v.size(); i++)
		totalVirus += v[i].virus;
	//根据答案要求进行MOD
	totalVirus %= 142857;
	cout << totalVirus << endl;

	return  0;
}
