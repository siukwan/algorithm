/*
题目描述

输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。

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
	vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
		vector<vector<int> >result(0);
		vector<int> path(0);
		dfs(root, 0, expectNumber, path, result);
		return result;
	}

	void dfs(TreeNode*root, int sum, int&target, vector<int> path, vector<vector<int>>&result)
	{
		if (root == NULL) return;
		sum += root->val;
		path.push_back(root->val);

		if (root->left == NULL && root->right == NULL)
		{
			if (sum == target)
				result.push_back(path);
			else
				return;
		}
		else
		{
			if (root->left)
				dfs(root->left, sum, target, path, result);
			if (root->right)
				dfs(root->right, sum, target, path, result);
		}
	}
};