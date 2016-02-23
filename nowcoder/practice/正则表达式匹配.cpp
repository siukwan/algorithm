/*
题目描述

请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配

*/
class Solution {
public:
	bool match(char* str, char* pattern)
	{

		string s = "", p = "";
		int pos = 0;
		while (str[pos] != 0)
			s += str[pos++];
		pos = 0;
		while (pattern[pos] != 0)
			p += pattern[pos++];
		/**
		* f[i][j]: if s[0..i-1] matches p[0..j-1]
		* if p[j - 1] != '*'
		*      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
		* if p[j - 1] == '*', denote p[j - 2] with x
		*      f[i][j] is true iff any of the following is true
		*      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
		*      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
		* '.' matches any single character
		*/
		int m = s.size(), n = p.size();
		vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));

		f[0][0] = true;
		for (int i = 1; i <= m; i++)
			f[i][0] = false;
		// p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
		for (int j = 1; j <= n; j++)
			f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];

		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				if (p[j - 1] != '*')
					f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
				else
					// p[0] cannot be '*' so no need to check "j > 1" here
					f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];

		return f[m][n];
	}
};