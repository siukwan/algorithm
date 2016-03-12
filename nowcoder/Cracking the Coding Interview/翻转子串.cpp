/*
题目描述

假定我们都知道非常高效的算法来检查一个单词是否为其他字符串的子串。请将这个算法编写成一个函数，给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成，要求只能调用一次检查子串的函数。
给定两个字符串s1,s2,请返回bool值代表s2是否由s1旋转而成。字符串中字符为英文字母和空格，区分大小写，字符串长度小于等于1000。
测试样例：
"Hello world","worldhello "
返回：false
"waterbottle","erbottlewat"
返回：true

*/
class ReverseEqual {
public:
	bool checkReverseEqual(string s1, string s2) {
		// write code here
		s2 += s2;

		vector<int> next(s1.size() + 1, 0);

		//求next数组
		for (int i = 1; i<s1.size(); ++i)
		{
			int j = next[i];
			while (j>0 && s1[i] != s1[j])
			{
				j = next[j];
			}
			if (s1[i] == s1[j])
			{
				next[i + 1] = j + 1;
			}
		}

		//KMP匹配
		int j = next[0];
		for (int i = 0; i<s2.size(); ++i)
		{
			while (j>0 && s2[i] != s1[j])
			{
				j = next[j];
			}
			if (s2[i] == s1[j])
				j++;
			if (j == s1.size())
				return true;
		}

		return false;
	}
};