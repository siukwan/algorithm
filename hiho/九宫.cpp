
//#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
#include<set>
#include<queue>
#include<map>
//#include<unordered_set>
#include<unordered_map>
//#include <sstream>
//#include "func.h"
//#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
#include<bitset>
//#include "siukwanAlloctor.h"
using namespace std;
bool check(vector<vector<int>>&a)
{
	vector<int> row(3, 0);
	vector<int> col(3, 0);
	vector<int> angle(2, 0);

	//计算行总和
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (a[i][j] == 0)
			{
				row[i] = 0;
				break;
			}
			else
				row[i] += a[i][j];
		}
		if (row[i] != 0 && row[i] != 15) return false;
	}

	//计算列总和
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (a[j][i] == 0)
			{
				col[i] = 0;
				break;
			}
			else
				col[i] += a[j][i];
		}
		if (col[i] != 0 && col[i] != 15) return false;
	}

	//计算对角线
	if (a[0][0] != 0 && a[1][1] != 0 && a[2][2] != 0)
		angle[0] = a[0][0] + a[1][1] + a[2][2];

	if (angle[0] != 0 && angle[0] != 15) return false;

	if (a[2][0] != 0 && a[1][1] != 0 && a[0][2] != 0)
		angle[1] = a[2][0] + a[1][1] + a[0][2];

	if (angle[1] != 0 && angle[1] != 15) return false;

	return true;

}

void dfs(vector<vector<int>>&a, int need, vector<bool>&used, vector<vector<vector<int>>>&result)
{
	if (result.size() >= 2) return;
	if (need == 0)
	{
		if (result.size() == 0)
			result.push_back(a);
		else
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					if (result[0][i][j] != a[i][j])
					{
						result.push_back(a);
						return;
					}
				}
			}
			return;
		}
	}
	for (int k = 1; k < used.size(); ++k)
	{
		if (!used[k])
		{
			used[k] = true;
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					if (a[i][j] == 0)//需要填充
					{
						a[i][j] = k;//填充为k
						if (check(a))//检测矩阵
							dfs(a, need - 1, used, result);
						a[i][j] = 0;//填充为k
					}
				}
			}
			used[k] = false;
		}
	}
}


int main()
{
	int need = 0;
	vector<vector<int>> a(3, vector<int>(3, 0));
	vector<bool> used(10, false);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			scanf("%d", &a[i][j]);
			if (a[i][j] == 0) need++;
			used[a[i][j]] = true;
		}
	}

	vector<vector<vector<int>>> result;
	dfs(a, need, used, result);
	if (result.size()>1)
		cout << "Too Many" << endl;
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				cout << result[0][i][j];
				if (j != 2)
					cout << " ";
				else
					cout << endl;
			}
		}
	}

	return 0;
}