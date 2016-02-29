/*
题目描述

编写代码，以给定值x为基准将链表分割成两部分，所有小于x的结点排在大于或等于x的结点之前
给定一个链表的头指针 ListNode* pHead，请返回重新排列后的链表的头指针。注意：分割以后保持原来的数据顺序不变。

*/
/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};*/
class Partition {
public:
	ListNode* partition(ListNode* pHead, int x) {
		// write code here
		if (pHead == NULL) return NULL;
		ListNode* a = new ListNode(0);
		ListNode* b = new ListNode(0);
		ListNode* preHeada = a;
		ListNode* preHeadb = b;

		while (pHead != NULL)
		{
			if (pHead->val<x)
			{
				a->next = pHead;
				a = a->next;
			}
			else
			{
				b->next = pHead;
				b = b->next;
			}
			pHead = pHead->next;
		}
		//需要清除b->next，避免出现环
		b->next = NULL;
		a->next = preHeadb->next;
		return preHeada->next;
	}
};