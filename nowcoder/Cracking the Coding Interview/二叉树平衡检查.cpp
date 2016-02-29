/*
题目描述

实现一个函数，检查二叉树是否平衡，平衡的定义如下，对于树中的任意一个结点，其两颗子树的高度差不超过1。
给定指向树根结点的指针TreeNode* root，请返回一个bool，代表这棵树是否平衡。

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

class Balance {
public:
	bool isBalance(TreeNode* root) {
		// write code here
		//要判断为空的状态
		if (root == NULL) return true;
		int a = treeHeight(root->left);
		int b = treeHeight(root->right);
		if (a - b >= -1 && a - b <= 1)
		{
			return isBalance(root->left) && isBalance(root->right);
		}
		else return false;
	}

	int treeHeight(TreeNode* root)
	{
		if (root == NULL)
			return 0;
		else return max(treeHeight(root->left), treeHeight(root->right)) + 1;
	}
};