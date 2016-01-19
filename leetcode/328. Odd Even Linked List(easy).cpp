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
	ListNode* oddEvenList(ListNode* head) {
		if (head == NULL) return head;
		else if (head->next == NULL) return head;
		else
		{
			ListNode* odd = head;
			ListNode* even = head->next;
			ListNode* a = odd;
			ListNode* b = even;
			head = head->next;
			head = head->next;
			while (head != NULL)
			{
				a->next = head;
				a = a->next;
				head = head->next;
				if (head != NULL)
				{//如果下一个节点不为空
					b->next = head;
					b = b->next;
					head = head->next;
				}
				else
				{//如果为空
					b->next = NULL;
					break;
				}
			}
			a->next = even;
			b->next = NULL;
			return odd;
		}

	}
};