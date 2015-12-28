/*
二叉树的镜像

题目描述

操作给定的二叉树，将其变换为源二叉树的镜像。

输入描述:

二叉树的镜像定义：源二叉树
     8
   /  \
  6    10
 / \   / \
5   7 9  11
镜像二叉树
     8
   /  \
  10    6
 / \   / \
11  9 7   5
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
	void Mirror(TreeNode *pRoot) {
		if (pRoot)
		{
			//交换左右子节点的值
			TreeNode *tmp = pRoot->left;
			pRoot->left = pRoot->right;
			pRoot->right = tmp;
			//递归进行交换
			Mirror(pRoot->left);
			Mirror(pRoot->right);
		}
	}
};