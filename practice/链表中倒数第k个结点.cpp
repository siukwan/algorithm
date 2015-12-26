/*
链表中倒数第k个结点

题目描述

输入一个链表，输出该链表中倒数第k个结点。
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
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		ListNode *first = pListHead;
		ListNode *next = pListHead;
		int i;
		for (i = 0; i<k&&next != NULL; i++)
		{
			next = next->next;
		}
		if (i != k) return NULL;
		while (next)
		{
			first = first->next;
			next = next->next;
		}
		return first;
	}
};