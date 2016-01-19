/*
变态跳台阶

题目描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
*/

#include <iostream>
#include <vector>

using namespace std;
/*
//dp[i] = dp[1]+dp[2]+dp[3]+....+dp[i-1]+1
class Solution {
public:
	int jumpFloorII(int number) {
		vector<int> dp(number + 1, 0);
		for (int i = 1; i <= number; ++i)
		{
			for (int j = 1; j < i; ++j)
				dp[i] += dp[j];
			dp[i]++;
		}
		return dp[number];
	}
};
*/

//实质为2^(number-1)
class Solution {
public:
	int jumpFloorII(int number) {
		if (number == 0) return 0;
		else
		{
			int result = 1;
			for (int i = 1; i < number; ++i)
				result *= 2;
			return result;
		}
	}
};
int main()
{
	Solution sols;
	cout << sols.jumpFloorII(1) << endl;
	return 0;
}
