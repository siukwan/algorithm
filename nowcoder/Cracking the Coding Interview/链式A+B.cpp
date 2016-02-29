/*
题目描述

有两个用链表表示的整数，每个结点包含一个数位。这些数位是反向存放的，也就是个位排在链表的首部。编写函数对这两个整数求和，并用链表形式返回结果。
给定两个链表ListNode* A，ListNode* B，请返回A+B的结果(ListNode*)。
测试样例：
{1,2,3},{3,2,1}
返回：{4,4,4}

*/
/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};*/
class Plus {
public:
	ListNode* plusAB(ListNode* a, ListNode* b) {
		// write code here
		ListNode* result = a;
		ListNode* preA;
		if (a == NULL) return b;
		int carry = 0;

		while (a != NULL&&b != NULL)
		{
			a->val += b->val + carry;
			carry = a->val / 10;
			a->val %= 10;
			preA = a;
			a = a->next;
			b = b->next;
		}

		if (a == NULL && b == NULL && carry != 0)
		{
			preA->next = new ListNode(carry);
		}
		else if (a != NULL && b == NULL)
		{
			a->val += carry;
			carry = a->val / 10;
			a->val %= 10;
			preA = a;
			a = a->next;
			while (carry&&a != NULL)
			{
				a->val += carry;
				carry = a->val / 10;
				a->val %= 10;
				preA = a;
				a = a->next;
			}
			if (a == NULL&&carry)
			{
				preA->next = new ListNode(carry);
			}
		}
		else if (a == NULL && b != NULL)
		{
			preA->next = b;
			a = b;
			a->val += carry;
			carry = a->val / 10;
			a->val %= 10;
			preA = a;
			a = a->next;
			while (carry&&a != NULL)
			{
				a->val += carry;
				carry = a->val / 10;
				a->val %= 10;
				preA = a;
				a = a->next;
			}
			if (a == NULL&&carry)
			{
				preA->next = new ListNode(carry);
			}
		}
		return result;
	}
};