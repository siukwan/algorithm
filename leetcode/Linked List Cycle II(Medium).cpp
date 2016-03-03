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
	ListNode *detectCycle(ListNode *pHead) {
		//使用两个指针，分别是慢指针和快指针
		ListNode* pTemp1 = pHead, *pTemp2 = pHead;
		while (pTemp1 != NULL && pTemp2->next != NULL) {
			pTemp1 = pTemp1->next;
			pTemp2 = pTemp2->next;
			if (pTemp2->next != NULL) {
				pTemp2 = pTemp2->next;
			}
			//两指针相遇，则退出
			if (pTemp1 == pTemp2) {
				break;
			}
		}
		if (pTemp2 != pTemp1) {
			return NULL;
		}

		//慢指针从头开始，快指针也改为每次走一步，相遇即为环的入口
		pTemp1 = pHead;
		while (pTemp1 != NULL && pTemp2->next != NULL) {
			if (pTemp1 == pTemp2) {
				return pTemp1;
			}
			pTemp1 = pTemp1->next;
			pTemp2 = pTemp2->next;

		}
		return NULL;
	}
};