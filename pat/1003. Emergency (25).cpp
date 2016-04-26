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
using namespace std;
#define maxDist 999999
struct vertexNode{
	vector<int> list;
	bool visited, sured;
	int pre;
	int cost;
};
struct cmp{
	bool operator()(const pair<int, int>&a, const pair<int, int>&b)
	{
		return a.second > b.second;
	}
};

void dfs(int now, int&target, vertexNode *v, int **w, int*rescue, vector<bool>&used, int &minCost, vector<int>&ans, int nowCost, int rescueTeam)
{
	if (now == target&&minCost == nowCost)
	{
		ans.push_back(rescueTeam);
	}
	else
	{
		for (int i = 0; i < v[now].list.size(); i++)
		{
			int q = v[now].list[i];
			if (!used[q] && nowCost + w[now][q] <= minCost)
			{//以最小耗费为约束条件
				used[q] = true;
				dfs(q, target, v, w, rescue, used, minCost, ans, nowCost + w[now][q], rescueTeam + rescue[q]);
				used[q] = false;
			}
		}
	}
}

int main(void) {

	int n, m, s, t;
	cin >> n >> m >> s >> t;

	int *rescue = new int[n];
	int *cost = new int[n];

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &rescue[i]);//输出各城市的救援队数目
		cost[i] = 99999999;//初始化cost
	}

	int **w = new int*[n];

	vertexNode *v = new vertexNode[n];
	for (int i = 0; i < n; i++)
	{
		w[i] = new int[n];
		memset(w[i], 0, sizeof(w[i]));
		v[i].cost = 99999999;
		v[i].pre = -1;
		v[i].list = vector<int>(0);
		v[i].sured = false;
		v[i].visited = false;
	}

	for (int i = 0; i < m; i++)
	{
		int a, b, weight;
		scanf("%d %d %d", &a, &b, &weight);
		v[a].list.push_back(b);
		v[b].list.push_back(a);
		w[a][b] = weight;
		w[b][a] = weight;
	}

	v[s].visited = true;
	v[s].pre = -1;
	v[s].cost = 0;
	while (1)
	{//采用dijkstra算法计算最小耗费
		int p = -1;
		for (int i = 0; i < n; i++)
		{
			if (p == -1 && v[i].visited&&!v[i].sured)
				p = i;
			else if (p != -1 && v[i].visited&&!v[i].sured&&v[p].cost > v[i].cost)
				p = i;
		}
		if (p == -1) break;
		v[p].sured = true;
		for (int i = 0; i < v[p].list.size(); i++)
		{
			int q = v[p].list[i];
			if (!v[q].visited)
			{
				v[q].cost = v[p].cost + w[p][q];
				v[q].visited = true;
				v[q].pre = p;
			}
			else if (v[q].visited&&!v[q].sured&&v[q].cost > v[p].cost + w[p][q])
			{
				v[q].cost = v[p].cost + w[p][q];
				v[q].visited = true;
				v[q].pre = p;
			}
		}
	}
	int minCost = v[t].cost;
	vector<bool> used(n, false);
	vector<int> ans(0);
	used[s] = true;
	dfs(s, t, v, w, rescue, used, minCost, ans, 0, rescue[s]);

	sort(ans.begin(), ans.end());
	cout << ans.size() << " " << ans.back() << endl;

	return 0;
}