/*
题目描述

地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？

*/
class Solution {
public:
	int movingCount(int threshold, int rows, int cols)
	{
		vector<bool> used(rows*cols, false);
		int result = 0;
		dfs(threshold, rows, cols, 0, 0, result, used);
		return result;
	}

	void dfs(int &threshold, int &rows, int &cols, int x, int y, int&result, vector<bool>&used)
	{
		if (intSum(x) + intSum(y) <= threshold&&
			x<rows&&y<cols && x >= 0 && y >= 0 &&
			!used[x*cols + y])
		{//题目中没有提到走过的格子不能走，所以不用解锁，每次直接锁used即可
			used[x*cols + y] = true;
			result++;
			dfs(threshold, rows, cols, x - 1, y, result, used);
			dfs(threshold, rows, cols, x, y - 1, result, used);
			dfs(threshold, rows, cols, x + 1, y, result, used);
			dfs(threshold, rows, cols, x, y + 1, result, used);
		}
	}

	int intSum(int a)
	{
		int result = 0;
		while (a != 0)
		{
			result += a % 10;
			a /= 10;
		}
		return result;
	}
};