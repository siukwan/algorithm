/*
题目描述

在一个字符串(1<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符的位置。若为空串，返回-1。位置索引从0开始
*/
class Solution {
public:
	int FirstNotRepeatingChar(string str) {
		if (str == "") return -1;
		map<char, int> m;
		for (int i = 0; i<str.size(); ++i)
		{
			m[str[i]]++;
		}
		int i = 0;
		bool flag = false;
		for (i = 0; i<str.size(); ++i)
		{
			if (m[str[i]] == 1)
			{
				flag = true;
				break;
			}
		}
		if (flag)
			return i;
		else
			return -1;
	}
};