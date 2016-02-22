/*
题目描述

从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。

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
	vector<vector<int> > Print(TreeNode* pRoot) {
		vector<vector<int>> result(0);
		if (pRoot == NULL) return result;

		queue<TreeNode*> q;
		q.push(pRoot);
		int count1 = 1;
		int count2 = 0;

		while (!q.empty())
		{
			vector<int> tmp(0);
			for (int i = 0; i<count1; ++i)
			{
				TreeNode* head = q.front();
				q.pop();
				tmp.push_back(head->val);

				if (head->left)
				{
					q.push(head->left);
					count2++;
				}
				if (head->right)
				{
					q.push(head->right);
					count2++;
				}
			}
			result.push_back(tmp);
			count1 = count2;
			count2 = 0;
		}
		return result;
	}

};