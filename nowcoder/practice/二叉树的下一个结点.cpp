/*
题目描述

给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
*/
using namespace std;
/*
struct TreeLinkNode {
int val;
struct TreeLinkNode *left;
struct TreeLinkNode *right;
struct TreeLinkNode *next;
TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

}
};
*/
class Solution {
public:
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		if (pNode->next == NULL && pNode->right == NULL)
			return NULL;
		//右孩子为空，父节点不为空
		else if (pNode->right == NULL && pNode->next != NULL)
		{
			//如果当前节点是右孩子
			if (pNode->next->right == pNode)
			{
				//一直往上找，直到当前节点是父节点的左孩子
				while (pNode != NULL&&pNode->next != NULL&&pNode->next->right == pNode)
				{
					pNode = pNode->next;
				}
				return pNode->next;
			}
			else//是左儿子
				return pNode->next;
		}
		//右孩子不为空，则返回右孩子的最左节点
		else
			return getLeft(pNode->right);
	}

	TreeLinkNode* getLeft(TreeLinkNode* root)
	{
		if (root->left != NULL)
			return getLeft(root->left);
		else
			return root;
	}
};
添加笔记
