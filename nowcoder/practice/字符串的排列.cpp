/*
题目描述

输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。 结果请按字母顺序输出。

输入描述:
输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母。

*/
class Solution {
public:
	vector<string> Permutation(string str) {
		vector<bool> used(str.size(), false);
		vector<string> result(0);
		if (str == "") return result;
		dfs(str, used, "", result);
		return result;
	}

	void dfs(string&str, vector<bool>&used, string tmp, vector<string>&result)
	{
		if (tmp.size() == str.size())
		{
			//防止重复
			for (int i = 0; i<result.size(); i++)
				if (result[i] == tmp)
					return;
			result.push_back(tmp);
		}
		else
		{
			for (int i = 0; i<str.size(); i++)
			{
				if (!used[i])
				{
					used[i] = true;
					dfs(str, used, tmp + str[i], result);
					used[i] = false;
				}
			}
		}
	}
};