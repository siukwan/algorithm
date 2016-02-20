/*
题目描述

输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点）。

*/
/*
struct RandomListNode {
int label;
struct RandomListNode *next, *random;
RandomListNode(int x) :
label(x), next(NULL), random(NULL) {
}
};
*/
class Solution {
public:
	RandomListNode* Clone(RandomListNode* pHead)
	{
		if (pHead == NULL) return NULL;
		long long head = (long long)pHead;
		map<long long, RandomListNode*> m;
		m[(long long)NULL] = NULL;
		while (pHead != NULL)
		{
			long long address = (long long)pHead;
			if (m.find(address) == m.end())
			{
				m[address] = new RandomListNode(pHead->label);
			}
			if (pHead->random != NULL)
			{
				if (m.find((long long)pHead->random) == m.end())
				{
					m[(long long)pHead->random] = new  RandomListNode(pHead->random->label);
				}
			}
			if (pHead->next != NULL)
			{
				if (m.find((long long)pHead->next) == m.end())
				{
					m[(long long)pHead->next] = new  RandomListNode(pHead->next->label);
				}
			}

			m[address]->next = m[(long long)pHead->next];
			m[address]->random = m[(long long)pHead->random];
			pHead = pHead->next;
		}
		return m[head];
	}
};