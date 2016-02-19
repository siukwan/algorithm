/*
题目描述

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。
*/
class Solution {
public:
	void reOrderArray(vector<int> &array) {
		for (int i = 0; i<array.size(); i++)
		{
			for (int j = array.size() - 1; j>i; j--)
			{
				if ((array[j - 1] & 0X1) == 0 && (array[j] & 0X1) == 1)
					swap(array[j - 1], array[j]);
			}
		}
	}
};