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
struct TreeNode{
	int val;
	TreeNode *l, *r;
	TreeNode(int x) :val(x), l(NULL), r(NULL){};
	TreeNode() :val(-1), l(NULL), r(NULL){};
};
TreeNode*dfs(vector<int>&node, int l, int r, bool&buildSuccess)
{//建立正常的BST
	if (l>r) return NULL;
	else if (l == r)
	{
		return new TreeNode(node[l]);
	}
	else
	{
		TreeNode* root = new TreeNode(node[l]);
		int i = l + 1;
		while (i <= r&&node[i]<root->val)
		{
			i++;
		}
		int j = i;
		while (j <= r&&node[j] >= root->val)
		{
			j++;
		}
		if (i != r + 1 && j != r + 1)
		{//如果i没有达到最终点且j也没有到达最终点，证明数组里面有部分点不满足要求，所以不能构建
			buildSuccess = false;
			return NULL;
		}
		root->l = dfs(node, l + 1, i - 1, buildSuccess);
		root->r = dfs(node, i, r, buildSuccess);
		return root;
	}
}


TreeNode*dfsMirror(vector<int>&node, int l, int r, bool&buildSuccess)
{//基本同上
	if (l>r) return NULL;
	else if (l == r)
	{
		return new TreeNode(node[l]);
	}
	else
	{
		TreeNode* root = new TreeNode(node[l]);
		int i = l + 1;
		while (i <= r&&node[i] >= root->val)
		{
			i++;
		}
		int j = i;
		while (j <= r&&node[j]<root->val)
		{
			j++;
		}
		if (i != r + 1 && j != r + 1)
		{
			buildSuccess = false;
			return NULL;
		}
		root->l = dfsMirror(node, l + 1, i - 1, buildSuccess);
		root->r = dfsMirror(node, i, r, buildSuccess);
		return root;
	}
}

void postOrderDFS(TreeNode*root, vector<int>&postOrder)
{
	if (root != NULL)
	{
		postOrderDFS(root->l, postOrder);
		postOrderDFS(root->r, postOrder);
		postOrder.push_back(root->val);
	}
}
/*
7 8 6 5 7 10 8 11

7 8 10 11 8 6 7 5

7 8 6 8 5 10 9 11
*/
int main(void)
{

	int nodeSum;
	cin >> nodeSum;
	vector<int> node(nodeSum);
	for (int i = 0; i<nodeSum; i++)
	{
		scanf("%d", &node[i]);
	}
	bool buildSuccess = true;
	TreeNode*tree = dfs(node, 0, (int)(node.size() - 1), buildSuccess);
	if (!buildSuccess)
	{
		buildSuccess = true;
		tree = dfsMirror(node, 0, (int)(node.size() - 1), buildSuccess);
	}
	if (buildSuccess)
	{
		cout << "YES" << endl;
		vector<int> postOrder(0);
		postOrderDFS(tree, postOrder);
		for (int i = 0; i<postOrder.size(); i++)
		{
			cout << postOrder[i];
			if (i != postOrder.size() - 1)
				cout << " ";
		}
		cout << endl;
	}
	else
		cout << "NO" << endl;
	return 0;
}