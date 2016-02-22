/*
题目描述

请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
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
	bool isSymmetrical(TreeNode* pRoot)
	{
		if (pRoot == NULL) return true;
		return isMirror(pRoot->left, pRoot->right);
	}
	bool isMirror(TreeNode* l, TreeNode* r)
	{
		if (l == NULL&&r == NULL) return true;
		else if (l != NULL&&r != NULL)
		{
			if (l->val == r->val)
			{
				return isMirror(l->left, r->right) && isMirror(l->right, r->left);
			}
			else
				return false;
		}
		else
			return false;
	}
};