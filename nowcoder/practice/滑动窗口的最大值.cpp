/*
题目描述

给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。

*/
class Solution {
public:
	vector<int> maxInWindows(const vector<int>& num, unsigned int size)
	{
		vector<int> result(0);
		//需要注意size=1和size=0的情况
		if (num.size()<size || size == 0) return result;
		map<int, int> counts;
		priority_queue<int> heap;
		for (int i = 0; i<size; ++i)
		{
			heap.push(num[i]);
			counts[num[i]]++;
		}
		result.push_back(heap.top());

		for (int i = size; i<num.size(); ++i)
		{
			counts[num[i - size]]--;
			counts[num[i]]++;

			while (!heap.empty() && counts[heap.top()] == 0)
			{//把出现次数为0的栈顶元素pop出去
				heap.pop();
			}
			heap.push(num[i]);
			result.push_back(heap.top());
		}

		return result;
	}
};