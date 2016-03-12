/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* oddEvenReverseList(ListNode* head) {
		if (head == NULL || head->next == NULL) return head;

		ListNode* pre = new ListNode(0);
		ListNode* result = new ListNode(0);
		pre->next = head;
		result = pre;

		while (head->next)
		{
			ListNode* tmp = head->next;
			head->next = head->next->next;
			tmp->next = pre->next;
			pre->next = tmp;
			pre = head;
			if (head->next)
				head = head->next;
			else break;

		}

		return result->next;

	}
};