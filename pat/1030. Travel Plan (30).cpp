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
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20

4 5 0 0
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
*/
struct neighbor
{
	int idx;
	int w;
	long long dist;
	neighbor() :idx(-1), w(-1), dist(-1){};
	neighbor(int a, int b, int c) :idx(a), w(b), dist(c){};
};
struct vertexNode{
	vector<neighbor> nb;
	bool visited;
	bool sured;
	long long dist;
	vertexNode() : nb(0), visited(false), sured(false), dist(INT_MAX){};
};

void dfs(int now, int t, int dist, int minDist, int cost, vector<int>& path, vector<pair<int, vector<int>>>& ans, vector<vertexNode>& v, vector<bool>&used)
{
	if (dist > minDist) return;
	if (now == t && dist == minDist)
	{
		ans.push_back({ cost, path });
	}
	else
	{
		for (int i = 0; i < v[now].nb.size(); i++)
		{
			int q = v[now].nb[i].idx;
			if (!used[q])
			{
				used[q] = true;
				path.push_back(q);
				dfs(q, t, dist + v[now].nb[i].dist, minDist, cost + v[now].nb[i].w, path, ans, v, used);
				path.pop_back();
				used[q] = false;
			}
		}
	}
}
bool cmp(const pair<int, vector<int>>&a, const pair<int, vector<int>>&b)
{
	return a.first < b.first;
}
int main(void)
{
	int cityNum, edgeNum, s, t;
	cin >> cityNum >> edgeNum >> s >> t;
	vector<vertexNode> v(cityNum);
	for (int i = 0; i < edgeNum; i++)
	{
		int a, b, d, w;
		scanf("%d %d %d %d", &a, &b, &d, &w);
		v[a].nb.push_back(neighbor(b, w, d));
		v[b].nb.push_back(neighbor(a, w, d));
	}

	v[s].visited = true;
	v[s].dist = 0;

	while (1)
	{
		int p = -1;
		for (int i = 0; i < v.size(); i++)
		{
			if (p == -1 && v[i].visited && !v[i].sured)
				p = i;
			else if (p != -1 && v[i].visited && !v[i].sured && v[p].dist > v[i].dist)
				p = i;
		}
		if (p == -1) break;
		v[p].sured = true;
		if (v[t].sured) break;
		for (int i = 0; i < v[p].nb.size(); i++)
		{
			int q = v[p].nb[i].idx;//获取邻居的编号
			if (!v[q].sured && v[q].dist > v[p].dist + v[p].nb[i].dist)
			{
				v[q].visited = true;
				v[q].dist = v[p].dist + v[p].nb[i].dist;
			}
		}
	}
	int minDist = v[t].dist;
	vector<int> path(0);
	path.push_back(s);
	vector < pair<int, vector<int>>> ans(0);
	vector<bool> used(cityNum, false);
	dfs(s, t, 0, minDist, 0, path, ans, v, used);
	sort(ans.begin(), ans.end(), cmp);
	for (int i = 0; i < ans[0].second.size(); i++)
	{
		cout << ans[0].second[i] << " ";
	}
	cout << minDist << " " << ans[0].first;
	return 0;
}