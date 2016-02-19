/*
题目描述
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

输入描述:
array： 待查找的二维数组
target：查找的数字

输出描述:
查找到返回true，查找不到返回false
*/
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
	bool Find(vector<vector<int> > array, int target) {
		//注意空数组，{}和{{}}是两种不同的情况
		if (array.size() == 0 || array[0].size() == 0) return false;
		int row = 0;
		int col = array[row].size() - 1;

		while (1)
		{
			if (target > array[row][col])
				row++;
			else if (target < array[row][col])
				col--;
			else
				return true;
			if (col < 0 || row > array.size() - 1 )
				return false;
		}
	}
};
int main()
{
	vector<vector<int>> array = { { 1, 2, 8, 9, 21 }, { 2, 4, 9, 12 ,22}, { 4, 7, 10, 13 ,23}, { 6, 8, 11, 15 ,24} };

	Solution sols;
	cout << sols.Find(array, 24) << endl;
	return 0;
}
