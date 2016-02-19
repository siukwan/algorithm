/*
题目描述

输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
*/
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

// Definition for binary tree
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	struct TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in) {
		if (pre.size() == 0) return NULL;
		int pos = 0;
		return dfs(pre, in, pos, 0, in.size() - 1);
	}
	struct TreeNode* dfs(vector<int>&pre, vector<int>&in, int rootPos, int inL, int inR)
	{
		//只有一个元素
		if (inL == inR)
		{
			TreeNode* root = new TreeNode(in[inL]);
			return root;
		}
		else if (inL > inR) return NULL;
		if (rootPos >= pre.size()) return NULL;
		TreeNode* root = new TreeNode(pre[rootPos]);
		int i;
		for (i = inL; i <= inR; ++i)
		{
			if (pre[rootPos] == in[i]) break;
		}
		rootPos++;
		root->left = dfs(pre, in, rootPos, inL, i - 1);
		rootPos+=(i-inL);//跳过接下来的i-inL个元素
		if (rootPos<pre.size())
			root->right = dfs(pre, in, rootPos, i + 1, inR);
		return root;
	}
};
int main()
{
	vector<int> pre = {  }; //{ 1, 2, 4, 7, 3, 5, 6, 8 };
	vector<int> in = { };//{ 4, 7, 2, 1, 5, 3, 8, 6 };
	Solution sols;
	TreeNode *a = sols.reConstructBinaryTree(pre, in);
	
	return 0;
}
