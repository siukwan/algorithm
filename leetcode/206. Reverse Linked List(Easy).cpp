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
	ListNode* reverseList(ListNode* head) {
		if (head == NULL || head->next == NULL) return head;
		ListNode* preHead = new ListNode(0);
		preHead->next = head;
		while (head->next != NULL)
		{
			ListNode* tmp = head->next;
			head->next = head->next->next;
			tmp->next = preHead->next;
			preHead->next = tmp;
		}
		return preHead->next;
	}
};