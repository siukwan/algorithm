/*
题目描述

用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution
{
public:
	void push(int node) {
		stack1.push(node);
	}

	int pop() {
		//如果stack2为空，则把stack1中的所有元素都放置到stack2，以后凡是pop，直接从stack2中pop即可
		if (stack2.empty())
		{
			while (!stack1.empty())
			{
				stack2.push(stack1.top());
				stack1.pop();
			}
		}
		int result = stack2.top();
		stack2.pop();
		return result;
	}

private:
	stack<int> stack1;
	stack<int> stack2;
};
int main()
{

	
	return 0;
}
