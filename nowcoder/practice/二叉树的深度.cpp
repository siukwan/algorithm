﻿/*
题目描述

输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
*/
class Solution {
public:
	int TreeDepth(TreeNode* pRoot)
	{
		if (pRoot == NULL) return 0;
		int l = TreeDepth(pRoot->left);
		int r = TreeDepth(pRoot->right);
		return max(l, r) + 1;
	}
};