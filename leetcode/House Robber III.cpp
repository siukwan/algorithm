/*
是一个树形DP的问题，如果父节点已经被偷，那么子节点不能被偷，父节点没被偷，子节点可以被偷或者不被偷。
相邻的父子节点不能同时被偷。

*/


/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
	map<TreeNode*, int> dp1;
	map<TreeNode*, int> dp2;
	int rob(TreeNode* root) {
		dfs(root);
		return max(dp1[root], dp2[root]);
	}
	void dfs(TreeNode* root)
	{
		if (root == NULL) return;

		//分别递归左右节点
		dfs(root->left);
		dfs(root->right);

		//偷这个节点
		dp1[root] = root->val + dp2[root->left] + dp2[root->right];
		//不偷这个节点
		dp2[root] = max(max(dp1[root->left] + dp1[root->right], dp2[root->left] + dp2[root->right]),
			max(dp2[root->left] + dp1[root->right], dp1[root->left] + dp2[root->right]));
	}
};