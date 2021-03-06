﻿/*
题目描述

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。

*/
/*
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};*/
class Solution {
public:
	TreeNode* Convert(TreeNode* pRootOfTree)
	{
		return dfs(pRootOfTree, false);
	}

	TreeNode* dfs(TreeNode *root, bool left)
	{
		if (root == NULL) return NULL;
		root->left = dfs(root->left, true);
		if (root->left)
			root->left->right = root;
		root->right = dfs(root->right, false);
		if (root->right)
			root->right->left = root;

		if (left)
		{
			while (root->right)
				root = root->right;
		}
		else
		{
			while (root->left)
				root = root->left;
		}
		return root;
	}
};