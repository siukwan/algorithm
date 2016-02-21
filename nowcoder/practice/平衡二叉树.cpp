/*
题目描述

输入一棵二叉树，判断该二叉树是否是平衡二叉树
*/
class Solution {
public:
	bool IsBalanced_Solution(TreeNode* pRoot) {
		int h;
		return height(pRoot, h);
	}
	bool height(TreeNode*pRoot, int&h)
	{
		if (pRoot == NULL)
		{
			h = 0;
			return true;
		}

		int l, r;
		bool left = height(pRoot->left, l);
		bool right = height(pRoot->right, r);
		if (left&&right&&l - r <= 1 && l - r >= -1)
		{
			h = max(l, r) + 1;
			return true;
		}
		else
			return false;
	}
};


//解法二
class Solution {
public:
	bool IsBalanced_Solution(TreeNode* pRoot) {
		if (pRoot == NULL) return true;
		int l = TreeDepth(pRoot->left);
		int r = TreeDepth(pRoot->right);
		if (l - r>1 || l - r<-1)
			return false;
		return IsBalanced_Solution(pRoot->left) && IsBalanced_Solution(pRoot->right);
	}
	int TreeDepth(TreeNode* pRoot)
	{
		if (pRoot == NULL) return 0;
		int l = TreeDepth(pRoot->left);
		int r = TreeDepth(pRoot->right);
		return max(l, r) + 1;
	}
};