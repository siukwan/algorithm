/*
题目描述

从上往下打印出二叉树的每个节点，同层节点从左至右打印

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
	vector<int> PrintFromTopToBottom(TreeNode *root) {
		vector<int> result(0);
		if (root == NULL) return result;
		queue<TreeNode*> q;
		int count1 = 1;
		int count2 = 0;
		q.push(root);
		while (!q.empty())
		{
			for (int i = 0; i<count1; i++)
			{
				TreeNode *tmp = q.front();
				q.pop();
				result.push_back(tmp->val);
				if (tmp->left)
				{
					q.push(tmp->left);
					count2++;
				}
				if (tmp->right)
				{
					q.push(tmp->right);
					count2++;
				}
			}
			count1 = count2;
			count2 = 0;
		}
		return result;

	}
};