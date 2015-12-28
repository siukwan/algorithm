/*
从尾到头打印链表

题目描述

输入一个链表，从尾到头打印链表每个节点的值。

输入描述:

输入为链表的表头


输出描述:

输出为需要打印的“新链表”的表头
*/

/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
	vector<int> printListFromTailToHead(struct ListNode* head) {
		ListNode*preHead = new ListNode(0);
		preHead->next = head;
		ListNode* now = head;

		vector<int> ans(0);
		//注意边界条件
		if (now == NULL) return ans;
		while (now->next)
		{
			//用一个临时指针指向now->next
			ListNode*tmp = now->next;
			now->next = tmp->next;
			tmp->next = preHead->next;
			preHead->next = tmp;
		}

		head = preHead->next;
		preHead = preHead->next;
		//把链表压进到vector中
		while (preHead)
		{
			ans.push_back(preHead->val);
			preHead = preHead->next;
		}
		return ans;
	}
};