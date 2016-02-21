/*
题目描述

输入两个链表，找出它们的第一个公共结点。
*/
/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};*/
class Solution {
public:
	ListNode* FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
		map<ListNode *, int>m;
		ListNode *tmp;
		tmp = pHead1;
		while (tmp)
		{
			m[tmp]++;
			tmp = tmp->next;
		}
		tmp = pHead2;
		while (tmp)
		{
			m[tmp]++;
			if (m[tmp] == 2) break;
			tmp = tmp->next;
		}
		return tmp;
	}
};