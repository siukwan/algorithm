/*
题目描述

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
*/
class Solution {
public:
	vector<int> printMatrix(vector<vector<int> > matrix) {
		vector<int> result(0);
		int i = 0, j = 0, xlow = -1, ylow = 0, xhigh, yhigh;//注意ylow，一开始就遍历第一行，所以ylow是0，xlow是-1
		if (matrix.size() == 0 || matrix[0].size() == 0) return result;
		xhigh = matrix[0].size();
		yhigh = matrix.size();
		int dir = 1;
		while (1)
		{
			if (xlow == xhigh || ylow == yhigh)
				break;
			if (dir == 1)//right
			{
				if (j == xhigh)
				{
					j--;
					xhigh--;
					dir = 2;
					i++;
				}
				else
				{
					result.push_back(matrix[i][j]);
					j++;
				}
			}
			else if (dir == 2)//down
			{
				if (i == yhigh)
				{
					i--;
					yhigh--;
					dir = 3;
					j--;
				}
				else
				{
					result.push_back(matrix[i][j]);
					i++;
				}
			}
			else if (dir == 3)//left
			{
				if (j == xlow)
				{
					j++;
					xlow++;
					dir = 4;
					i--;
				}
				else
				{
					result.push_back(matrix[i][j]);
					j--;
				}
			}
			else if (dir == 4)//up
			{
				if (i == ylow)
				{
					i++;
					ylow++;
					dir = 1;
					j++;
				}
				else
				{
					result.push_back(matrix[i][j]);
					i--;
				}
			}
		}
		return result;
	}
};