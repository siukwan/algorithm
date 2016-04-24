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
struct node{
	vector<string> child;
	int head;
	string ID;
	node() :head(-1), child(0), ID(""){};
};

int main(void) {

	int n, m;
	cin >> n >> m;

	map<string, node> tree;
	for (int i = 0; i < m; i++)
	{//循环输入父子关系
		string ID;
		cin >> ID;
		tree[ID].ID = ID;
		int k;
		cin >> k;
		for (int i = 0; i < k; i++)
		{
			string tmp;
			cin >> tmp;
			if (tmp.size() == 1)
				tmp = "0" + tmp;//避免出现单位的数字如1，2，3，4；题目要求是两位数，所以是01，02，03，04
			tree[ID].child.push_back(tmp);
			tree[tmp].ID = tmp;
			tree[tmp].head++;
		}
	}
	//需要建立一个前头节点，便于循环计算
	tree["superhead"].ID = "";
	tree["superhead"].child = vector<string>(0);
	tree["superhead"].head = 100;
	string headID = "";
	tree["superhead"].child.push_back("01");
	headID = "superhead";
	queue<string> q;
	q.push(headID);
	vector<int> ans(0);
	int count1 = 1;
	int count2 = 0;
	int leaf = 0;
	while (!q.empty())
	{
		for (int k = 0; k < count1; k++)
		{//上一层有count1个
			string top = q.front();
			q.pop();
			for (int i = 0; i < tree[top].child.size(); i++)
			{
				string tmp = tree[top].child[i];
				if (tree[tmp].child.size() == 0)
					leaf++;//如果没有子节点，那么就是叶子节点
				else
				{
					q.push(tmp);//有子节点，压进队列，继续遍历
					count2++;
				}
			}
		}
		ans.push_back(leaf);
		leaf = 0;
		count1 = count2;
		count2 = 0;
	}
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i];
		if (i != ans.size() - 1)
			cout << " ";
	}
	return 0;
}