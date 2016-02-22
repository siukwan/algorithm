/*
题目描述

一个链表中包含环，请找出该链表的环的入口结点。

*/
/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};
*/
class Solution {
public:
	ListNode* EntryNodeOfLoop(ListNode* pHead)
	{
		if (pHead == NULL) return NULL;
		ListNode*a = pHead, *b = pHead;
		while (a != NULL&&b->next != NULL)
		{
			a = a->next;
			b = b->next;
			if (b->next != NULL)
				b = b->next;

			if (a == b) break;
		}

		if (a != b) return NULL;

		a = pHead;
		while (a != NULL&&b->next != NULL)
		{
			if (a == b) return a;
			a = a->next;
			b = b->next;
		}
		return NULL;


	}
};