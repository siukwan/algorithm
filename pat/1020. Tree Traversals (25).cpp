//#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
#include<set>
#include<queue>
#include<map>
//#include<unordered_set>
//#include<unordered_map>
//#include <sstream>
//#include "func.h"
//#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
using namespace std;
class TreeNode{
public:
	int val;
	TreeNode* l, *r;
	TreeNode(int x) :val(x), l(NULL), r(NULL){};
	TreeNode() :val(0), l(NULL), r(NULL){};
};
TreeNode* build(vector<int>&postOrder, int postStart, int postEnd,
	vector<int>&inOrder, int inStart, int inEnd, int&index, vector<TreeNode>&tree)
{
	if (postStart == postEnd)
	{//如果start和end相同，即这个是叶子节点
		tree[index++] = TreeNode(postOrder[postEnd]);
		return &tree[index - 1];
	}
	else if (postStart > postEnd) return NULL;
	else
	{
		int rootVal = postOrder[postEnd];//后序遍历的末位是根
		int rootPos = inStart;//根在中序遍历中的位置
		for (; rootPos <= inEnd; rootPos++)
		{
			if (rootVal == inOrder[rootPos])
				break;
		}
		int returnNode = index++;
		tree[returnNode] = TreeNode(rootVal);
		//注意newPostEnd = postStart + rootPos - inStart-1
		tree[returnNode].l = build(postOrder, postStart, postStart + rootPos - inStart - 1, inOrder, inStart, rootPos - 1, index, tree);
		tree[returnNode].r = build(postOrder, postStart + rootPos - inStart, postEnd - 1, inOrder, rootPos + 1, inEnd, index, tree);
		return &tree[returnNode];

	}
}
int main(void)
{
	int nodeNum;
	cin >> nodeNum;
	vector<int> postOrder(nodeNum, 0);//后序
	vector<int> inOrder(nodeNum, 0);//中序

	for (int i = 0; i < nodeNum; i++)
	{
		cin >> postOrder[i];
	}
	for (int i = 0; i < nodeNum; i++)
	{
		cin >> inOrder[i];
	}
	vector<TreeNode> tree(nodeNum);//提前分配后内存空间，方便后面的连接
	int index = 0;
	TreeNode*ans = build(postOrder, 0, nodeNum - 1, inOrder, 0, nodeNum - 1, index, tree);

	int total = 0;
	int total2 = 0;
	queue<TreeNode*> q;
	if (ans != NULL)
	{
		total = 1;
		q.push(ans);
	}
	vector<int> outNum(0);
	while (!q.empty())
	{//进行BFS
		while (total--)
		{
			TreeNode* front = q.front(); q.pop();
			outNum.push_back(front->val);
			if (front->l != NULL)
			{
				q.push(front->l);
				total2++;
			}
			if (front->r != NULL)
			{
				q.push(front->r);
				total2++;
			}

		}
		total = total2;
		total2 = 0;
	}
	for (int i = 0; i < outNum.size(); i++)
	{
		cout << outNum[i];
		if (i != outNum.size() - 1)
			cout << " ";
	}

	return 0;
}