/*
题目描述

请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。

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
		int level = 1;

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

			if ((level & 0x1) == 0)
			{
				for (int i = 0; i<tmp.size() / 2; ++i)
					swap(tmp[i], tmp[tmp.size() - 1 - i]);
			}
			result.push_back(tmp);
			level++;
			count1 = count2;
			count2 = 0;
		}

		return result;
	}

};