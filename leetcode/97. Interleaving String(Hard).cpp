class Solution {
public:
	bool isInterleave(string s1, string s2, string s3) {
		int m = s1.size();
		int n = s2.size();
		int k = s3.size();
		if (m + n != k) return false;
		else if (m == 0 && n == 0) return true;
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
		//定义dp[i][j]为当s1剩余i个字符，s2剩余j个字符时，能否组成s3.substr(i+j);
		for (int i = 0; i<m + 1; i++)
		{
			for (int j = 0; j<n + 1; j++)
			{
				char tmp_s3 = s3[k - i - j];
				char tmp_s1 = s1[m - i];
				char tmp_s2 = s2[n - j];
				if (i == 0 && j == 0) dp[0][0] = true;
				else
				{
					if (tmp_s1 == tmp_s3&&tmp_s2 == tmp_s3)
					{//如果两个都可以，说明当前状态可以从dp[i][j-1]转换来，也可以从dp[i-1][j]转换来
						//从dp[i][j-1]转换来,说明多了一个j
						//从dp[i-1][j]转换来,说明多了一个i
						dp[i][j] = (dp[i][j - 1] || dp[i - 1][j]);
					}
					else if (s3[k - i - j] == s2[n - j] && j>0)
					{//只有s2的字符相同，比较的是j，说明多出一个j，dp[i][j]只和dp[i][j-1]有联系
						dp[i][j] = dp[i][j - 1];
					}
					else if (s3[k - i - j] == s1[m - i] && i>0)
					{//只有s1的字符相同，比较的是i，说明多出一个i，dp[i][j]只和dp[i-1][j]有联系
						dp[i][j] = dp[i - 1][j];
					}
					else
						dp[i][j] = false;
				}
			}
		}
		return dp[m][n];
	}
};