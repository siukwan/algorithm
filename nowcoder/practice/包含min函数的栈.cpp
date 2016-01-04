/*
题目描述

定义栈的数据结构，请在该类型中实现一个能够得到栈最小元素的min函数。

题解：
使用一个小根堆和一个元素出现次数数组来维护这个栈；
每次push一个元素，该元素出现次数+1，并把该元素压进小根堆
每次pop一个元素，该元素出现次数-1，如果小根堆的栈顶元素出现次数为0，则一直pop，直到栈顶元素出现次数不为0
*/
class Solution {
public:

	stack<int> s;
	map<int, int> m;
	static struct cmp
	{
		bool operator()(const int&a, const int &b)
		{
			return a>b;
		}
	};
	priority_queue<int, vector<int>, cmp> pq;

	void push(int value) {
		s.push(value);
		pq.push(value);
		m[value]++;
	}
	void pop() {
		m[s.top()]--;
		s.pop();
		while (m[pq.top()] == 0)
			pq.pop();
	}
	int top() {
		return s.top();
	}
	int min() {
		return pq.top();
	}
};