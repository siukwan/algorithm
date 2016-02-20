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


//这是O(n)复杂度的算法，先对每个节点进行复制，并附加到原链表，使得奇数位置节点为原链表节点，偶数位置节点为新链表节点
//最后进行分离
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
		copyNext(pHead);
		copyRandom(pHead);
		return destructList(pHead);
	}

	//复制链表，每个节点后面紧跟着复制出来的节点
	void copyNext(RandomListNode* pHead)
	{
		if (pHead == NULL) return;
		while (pHead)
		{
			RandomListNode* tmp = new RandomListNode(pHead->label);
			tmp->next = pHead->next;
			pHead->next = tmp;
			pHead = tmp->next;
		}
	}

	void copyRandom(RandomListNode* pHead)
	{
		if (pHead == NULL) return;
		while (pHead)
		{
			if (pHead->random)
				pHead->next->random = pHead->random->next;
			pHead = pHead->next->next;
		}
	}

	RandomListNode* destructList(RandomListNode* pHead)
	{
		if (pHead == NULL) return NULL;
		RandomListNode* result = pHead->next;
		RandomListNode* tmp = new RandomListNode(0);
		while (pHead)
		{
			tmp->next = pHead->next;
			tmp = tmp->next;
			pHead->next = tmp->next;
			pHead = pHead->next;
		}
		return result;
	}

};