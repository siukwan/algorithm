/*
题目描述

请编写一个函数，检查链表是否为回文。
给定一个链表ListNode* pHead，请返回一个bool，代表链表是否为回文。
测试样例：
{1,2,3,2,1}
返回：true
{1,2,3,2,3}
返回：false

*/
/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};*/
class Palindrome {
public:
	bool isPalindrome(ListNode* pHead) {
		// write code here
		if (pHead == NULL) return false;
		vector<int> a;
		while (pHead != NULL)
		{
			a.push_back(pHead->val);
			pHead = pHead->next;
		}

		for (int i = 0; i<a.size() / 2; ++i)
		{
			if (a[i] != a[a.size() - 1 - i])
				return false;
		}
		return true;
	}
};