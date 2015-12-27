/*
题目：
1.实则为一个01背包问题。
2.使用动态规划求解：
dp[i][j]表示从前i个物品开始选择，重量不超过j时，背包的最大价值。
dp[n][m]为最终答案。
状态转移方程为：

//背包空余重量不足
if (weight[i]>j) dp[i + 1][j] = dp[i][j];
//动态规划，选和不选的情况
else
dp[i + 1][j] = max(dp[i][j], dp[i][j - weight[i]] + value[i]);

3.写了两个版本，其中一个是没有优化的，一个是优化的版本。其中需要注意：
（1）优化版本只采用dp[j]
（2）因为dp[i + 1][j] = max(dp[i][j], dp[i][j - weight[i]] + value[i])需要使用到dp[i][j-weight[i]]的值，所以在遍历重量的时候需要从后面开始遍历：
for (int j = m; j >= 0; j--)

*/
/*
*/

#include<string>
#include <iomanip>
#include<fstream>
#include<set>
#include<queue>
#include<map>
//#include<unordered_set>
//#include<unordered_map>
//#include <sstream>
//#include "func.h"
//#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
//#include<stack>
#include<vector>
#include <algorithm>
using namespace std;

/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	/*
	int n, m;
	cin >> n >> m;
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	vector<int> value(n, 0);
	vector<int> weight(n, 0);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &weight[i], &value[i]);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			//背包空余重量不足
			if (weight[i]>j) dp[i + 1][j] = dp[i][j];
			//动态规划，选和不选的情况
			else
				dp[i + 1][j] = max(dp[i][j], dp[i][j - weight[i]] + value[i]);
		}
	}

	cout << dp[n][m] << endl;
	*/

	//优化版本:
	int n, m;
	cin >> n >> m;
	vector<int> dp(m + 1, 0);
	vector<int> value(n, 0);
	vector<int> weight(n, 0);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &weight[i], &value[i]);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = m; j >= 0; j--)
		{//因为dp[j-weight[i]]是引用了前面的数组，所以需要从后面开始遍历
			//背包空余重量不足
			if (weight[i]>j) dp[j] = dp[j];
			//动态规划，选和不选的情况
			else
				dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
		}
	}

	cout << dp[m] << endl;


	return  0;
}
