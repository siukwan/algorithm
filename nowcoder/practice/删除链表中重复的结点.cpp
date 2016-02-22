/*
题目描述

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5

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
	ListNode* deleteDuplication(ListNode* pHead)
	{
		ListNode* preHead = new ListNode(0);
		preHead->next = pHead;
		ListNode* result;
		result = preHead;

		while (pHead)
		{
			if (pHead->next)
			{
				//值相同，需要删除
				if (preHead->next->val == pHead->next->val)
				{
					while (pHead->next != NULL&&preHead->next->val == pHead->next->val)
					{
						pHead = pHead->next;
					}
					if (pHead->next != NULL)
						preHead->next = pHead->next;
					else
						preHead->next = NULL;

					pHead = preHead->next;
				}
				else
				{
					preHead = preHead->next;
					pHead = pHead->next;
				}
			}
			else
				break;
		}
		return result->next;
	}
};