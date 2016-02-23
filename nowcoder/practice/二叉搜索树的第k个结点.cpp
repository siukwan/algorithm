/*
题目描述

给定一颗二叉搜索树，请找出其中的第k大的结点。例如， 5 / \ 3 7 /\ /\ 2 4 6 8 中，按结点数值大小顺序第三个结点的值为4。

*/
/*
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};
*/
class Solution {
public:
	TreeNode* KthNode(TreeNode* pRoot, unsigned int k)
	{
		vector<TreeNode*> in(0);
		dfs(pRoot, in);
		if (in.size()<k || k == 0 || in.size() == 0) return NULL;
		else return in[k - 1];
	}
	void dfs(TreeNode* root, vector<TreeNode*>&in)
	{
		if (root == NULL) return;
		dfs(root->left, in);
		in.push_back(root);
		dfs(root->right, in);
	}

};