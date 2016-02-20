/*
题目描述

输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
	vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
		size = 0;
		heap = vector<int>(k + 1, 0);
		heap[0] = INT_MAX;
		vector<int> result(0);
		if (k == 0) return result;
		if (k>input.size()) return result;
		result = vector<int>(k, 0);

		for (int i = 0; i<input.size(); i++)
		{
			if (size >= k&&heap[0] >= input[i])
			{
				push(input[i]);
				pop();
			}
			else if (size < k)
				push(input[i]);
		}

		for (int i = 0; i<k; i++)
		{
			result[k - 1 - i] = heap[0];
			pop();
		}

		return result;
	}

	vector<int> heap;
	int size;

	void push(int x)
	{
		int insertPos = size++;
		int i = insertPos;
		int p = (i - 1) / 2;
		while (x>heap[p])
		{
			heap[i] = heap[p];
			if (i == 0) break;
			i = p;
			p = (i - 1) / 2;
		}
		heap[i] = x;
	}

	void pop()
	{
		int bottom = heap[size - 1];
		int i = 0;
		int a = 2 * i + 1, b = 2 * i + 2;
		size--;
		while (a<size)
		{
			if (b<size&&heap[a]<heap[b]) a = b;
			if (bottom<heap[a])
				heap[i] = heap[a];
			else break;
			i = a;
			a = 2 * i + 1;
			b = 2 * i + 2;
		}
		heap[i] = bottom;
	}
};
int main()
{
	Solution sols;
	vector<int> input = { 4, 5, 1, 6, 2, 7, 3, 8 };

	vector<int> result = sols.GetLeastNumbers_Solution(input, 4);
	
	return 0;
}
