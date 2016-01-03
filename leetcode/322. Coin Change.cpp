//#include<string>
//#include <iomanip>
#include<fstream>
//#include<set>
//#include<queue>
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
#include<stack>
#include<vector>
#include <algorithm>

#include <time.h>  
#include <windows.h> 
#include <tchar.h>

using namespace std;
/*
和完全背包问题类似
定义dp[i][j]为前i个硬币，能够组成价值为j时硬币数的最小值


if(coins[i]<=j)
dp[i+1][j] = min(dp[i][j],dp[i+1][j-coins[i]]+1)
else
dp[i+1][j]=dp[i][j]
*/


class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {

		vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, 1000000));
		//初始化边界条件
		for (int i = 0; i < coins.size(); i++)
		{
			if (coins[i] <= amount)
				dp[0][coins[i]] = 1;
		}
		//初始化边界条件
		for (int i = 0; i < dp.size(); i++)
		{
			dp[i][0] = 0;
		}

		//进行动态规划
		for (int i = 0; i<coins.size(); i++)
		{
			for (int j = 0; j <= amount; j++)
			{
				if (coins[i] <= j)
					dp[i + 1][j] = min(dp[i][j], dp[i + 1][j - coins[i]] + 1);
				else
					dp[i + 1][j] = dp[i][j];
			}
		}
		if (dp[coins.size()][amount] == 1000000) return -1;
		else return dp[coins.size()][amount];

	}
};
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	Solution sols;
	vector<int> coins = { 1 };
	int a = sols.coinChange(coins, 0);
	return  0;
}
