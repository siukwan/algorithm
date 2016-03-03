/*
思路：
1.定义一个慢指针，每次走一步，定义一个快指针，每次走两步
2.设起始点到环入口的距离为start
3.当两个指针相遇时，设环入口到指针相遇地点的距离为common
4.快指针走的路程为2*x=start+common+n*loop
5.慢指针走的路程为  x=start+common
6.上面两个式子相减得x=n*loop=start+common = (n-1)*loop + common + (loop- common)
7.所以 start = （n-1）*loop + （loop - common）
8.所以后面令一个指针从头开头走，另外一个指针从相遇点开始走，两个指针每次都走一步，则它们遇见的地方距离第一次相遇相差common，即为环的入口。

*/


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