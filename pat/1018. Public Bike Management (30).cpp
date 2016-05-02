

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <memory.h>
#include "limits.h"
using namespace std;

class vertexNode{
public:
	vector<int> list;
	bool visited, sured;
	long long cost;
	int cap;
	vertexNode() :list(0), visited(false), sured(false), cost(INT_MAX), cap(0){};
};

void dfs(vector<bool> & used, int now, int target,
	long long nowCost, long long &minCost, vector<vector<int>>&ans, vector<int>&path, vector<vertexNode>& v,
	vector<vector<long long>>&w)
{
	if (now == target&&nowCost == minCost)
	{
		ans.push_back(path);
	}
	else
	{
		for (int i = 0; i < v[now].list.size(); i++)
		{
			int p = v[now].list[i];
			if (!used[p] && nowCost + w[now][p] <= minCost)
			{
				used[p] = true;
				path.push_back(p);
				dfs(used, p, target, nowCost + w[now][p], minCost, ans, path, v, w);
				path.pop_back();
				used[p] = false;
			}
		}
	}
};

int main(void)
{
	int capMax, n, sp, m;
	cin >> capMax >> n >> sp >> m;
	n++;//PBMC记为0，接下来的城市为1~n，所以n++
	vector<vertexNode> v(n);
	for (int i = 1; i < n; i++)
	{
		cin >> v[i].cap;
	}
	vector<vector<long long> > w(n, vector<long long>(n, INT_MAX));
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		if (w[a][b] > c)
		{
			w[a][b] = c;
			w[b][a] = c;
			v[a].list.push_back(b);
			v[b].list.push_back(a);
		}
	}

	v[0].visited = true;
	v[0].cap = 0;
	v[0].cost = 0;
	while (1)
	{
		int p = -1;
		for (int i = 0; i < n; i++)
		{//找出已经探索的最小耗费的点
			if (p == -1 && v[i].visited&&!v[i].sured)
				p = i;
			else if (p != -1 && v[i].visited&&!v[i].sured && v[p].cost > v[i].cost)
				p = i;
		}
		if (p == -1) break;
		v[p].sured = true;//确定p点
		if (v[sp].sured) break;//目标点的最短路径确认后，不再遍历
		for (int i = 0; i < v[p].list.size(); i++)
		{
			int q = v[p].list[i];
			if (!v[q].sured && v[p].cost + w[p][q] < v[q].cost)
			{//更新最短路径
				v[q].visited = true;
				v[q].cost = v[p].cost + w[p][q];
			}
		}
	}

	vector<bool> used(n, false);
	long long minCost = v[sp].cost;//最小耗费
	vector<vector<int>> ans(0, vector<int>(0));
	vector<int> path(0);
	dfs(used, 0, sp, 0, minCost, ans, path, v, w);
	int minSendBike = INT_MAX;
	int minCurBike = INT_MAX;
	int minIndex = -1;
	for (int i = 0; i < ans.size(); i++)
	{//遍历每个答案
		int sendBike = 0;
		int curBike = 0;
		int perfectCap = capMax / 2;
		for (int j = 0; j < ans[i].size(); j++)
		{
			if (v[ans[i][j]].cap + curBike < perfectCap)
			{//如果当前单车总数加上节点的现有单车数都达不到完美容量，则需要send
				sendBike += perfectCap - v[ans[i][j]].cap - curBike;
				curBike = 0;
			}
			else
			{
				curBike = v[ans[i][j]].cap + curBike - perfectCap;
			}
		}
		if (minSendBike>sendBike)
		{//如果发送单车数量小于当前最小值，则更新
			minSendBike = sendBike;
			minIndex = i;
			minCurBike = curBike;
		}
		else if (minSendBike == sendBike && minCurBike>curBike)
		{//如果send的数量相同，则判断需要take的最小值，进行更新
			minSendBike = sendBike;
			minIndex = i;
			minCurBike = curBike;
		}

	}
	long long send;
	long long take;
	send = minSendBike;
	take = minCurBike;
	cout << send << " ";
	if (ans[minIndex].size() > 0)
	{
		cout << "0";
		for (int i = 0; i < ans[minIndex].size(); i++)
		{
			cout << "->" << ans[minIndex][i];
		}
	}
	cout << " " << take << endl;


	return 0;
}