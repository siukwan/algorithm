/*
在N*M的草地上,提莫种了K个蘑菇,蘑菇爆炸的威力极大,兰博不想贸然去闯,而且蘑菇是隐形的.只 有一种叫做扫描透镜的物品可以扫描出隐形的蘑菇,于是他回了一趟战争学院,买了2个扫描透镜,一个 扫描透镜可以扫描出(3*3)方格中所有的蘑菇,然后兰博就可以清理掉一些隐形的蘑菇. 问:兰博最多可以清理多少个蘑菇?

输入描述:

第一行三个整数:N,M,K,(1≤N,M≤20,K≤100),N,M代表了草地的大小;
接下来K行,每行两个整数x,y(1≤x≤N,1≤y≤M).代表(x,y)处提莫种了一个蘑菇.
一个方格可以种无穷个蘑菇.


输出描述:

输出一行,在这一行输出一个整数,代表兰博最多可以清理多少个蘑菇.

*/

//需要注意的是，每次使用，一个格子里一次只能清理1个蘑菇

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
using namespace std;


//对(x,y)在内的9个空格进行蘑菇检测，并返回删除的蘑菇数量
int clear(int x, int y, vector<vector<int>>& res, bool act)
{
	int count = 0;
	for (int i = x - 1; i <= x + 1; ++i)
	{
		for (int j = y - 1; j <= y + 1; ++j)
		{
			if (i >= 0 && i < res.size() && j >= 0 && j < res[i].size())
			{
				if (res[i][j] > 0)
				{
					if (act)
						res[i][j]--;
					count++;
				}
			}
		}
	}
	return count;
}

int main(void)
{
	int n, m, k;
	while (scanf("%d %d %d", &n, &m, &k) != EOF)
	{
		vector<vector<int>> oldMap(n, vector<int>(m, 0));
		vector<vector<int>> newMap = oldMap;
		for (int i = 0; i < k; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			oldMap[x - 1][y - 1]++;
		}

		int maxResult = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				//进行第一次清除蘑菇
				newMap = oldMap;
				int ans = clear(i, j, newMap, true);

				//进行第二次清除蘑菇
				for (int q = i; q < n; ++q)
				{
					for (int p = 0; p < m; ++p)
					{
						int tmp = clear(q, p, newMap, false);
						if (ans + tmp>maxResult)
							maxResult = ans + tmp;
					}
				}


			}
		}
		printf("%d\n", maxResult);
	}

	return 0;
}