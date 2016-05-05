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
class VertexNode{
public:
	vector<int> list;
	VertexNode() :list(0){};
};
int findRepresent(int a, int* r)
{
	if (r[a] == a)
		return a;
	else
	{
		r[a] = findRepresent(r[a], r);
		return r[a];
	}
}
void dfs(int&node, VertexNode *v, int &maxDeep, int deep, int&root, bool*used, vector<pair<int, int>>&ans)
{
	bool visitedAll = true;
	for (int i = 0; i < v[node].list.size(); i++)
	{
		int p = v[node].list[i];
		if (!used[p])
		{
			used[p] = true;
			visitedAll = false;
			dfs(p, v, maxDeep, deep + 1, root, used, ans);
			used[p] = false;
		}
	}
	if (visitedAll&&deep >= maxDeep)
	{
		maxDeep = deep;
		ans.push_back({ root, deep });
	}
}
bool cmp(const pair<int, int>&a, const pair<int, int>&b)
{
	if (a.second>b.second)
		return true;
	else if (a.second == b.second && a.first < b.first)
		return true;
	else
		return false;
}
int main(void)
{
	int nodeNum;
	cin >> nodeNum;
	//VertexNode *v = new VertexNode[nodeNum];//节点
	vector<VertexNode> v(nodeNum);
	vector<int> temp(0);
	for (int i = 0; i < nodeNum - 1; i++)
	{
		v[i].list = temp;
	}
	int *r = new int[nodeNum];//代表
	for (int i = 0; i < nodeNum; i++)
		r[i] = i;
	for (int i = 0; i < nodeNum - 1; i++)
	{
		int a, b;
		cin >> a >> b; a--; b--;
		v[a].list.push_back(b);
		v[b].list.push_back(a);
		r[findRepresent(a, r)] = findRepresent(b, r);//合并a和b
	}
	int setNum = 0;
	for (int i = 0; i < nodeNum; i++)
	{//并查集检测集合数量
		if (i == r[i]) setNum++;
	}
	delete[]r;
	if (setNum >= 2)
	{
		printf("Error: %d components\n", setNum);
		return 0;
	}

	/*bool *used = new bool[nodeNum];
	memset(used, false, sizeof(used));*/
	vector<bool> used(nodeNum, false);
	vector<pair<int, int>> ans(0);
	int maxDeep = 0;

	for (int root = 0; root < nodeNum; root++)
	{//对每一个点使用广度优先搜索,BFS
		//memset(used, false, sizeof(used));

		vector<bool> used = vector<bool>(nodeNum, false);
		queue<int>q;
		q.push(root);
		int total = 1;
		int total2 = 0;
		int deep = 0;
		used[root] = true;
		//cout << "root:" << root << endl;
		while (!q.empty())
		{
			deep++;
			//cout << "layer" << deep << " :";
			for (int i = 0; i < total; ++i)
			{
				int top = q.front(); q.pop();
				for (int j = 0; j < v[top].list.size(); ++j)
				{
					int p = v[top].list[j];
					if (!used[p])
					{
						//cout << p << " ";
						used[p] = true;
						q.push(p);
						total2++;
					}
				}
			}
			total = total2;
			total2 = 0;
			//cout << endl;
		}
		//cout << endl;
		if (deep >= maxDeep)
		{
			maxDeep = deep;
			ans.push_back({ root, deep });
		}
	}

	sort(ans.begin(), ans.end(), cmp);
	for (int i = 0; i < nodeNum; i++)
	{
		used[i] = false;
	}
	for (int i = 0; i < ans.size(); i++)
	{
		if (ans[i].second == maxDeep)
		{
			used[ans[i].first] = true;
			//cout << ans[i].first << endl;
		}
		else break;
	}
	for (int i = 0; i < nodeNum; i++)
	{
		if (used[i])
			cout << i + 1 << endl;
	}
	return 0;
}