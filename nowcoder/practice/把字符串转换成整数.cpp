/*
题目描述

将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。

*/
class Solution {
public:
	int StrToInt(string str) {
		int result = 0;
		if (str.size() == 0) return result;
		bool sign = true;
		if (str[0] == '-')
		{
			sign = false;
			str = str.substr(1);
		}
		else if (str[0] == '+')
		{
			str = str.substr(1);
		}
		for (int i = 0; i<str.size(); ++i)
		{
			//包含其他符号
			if (str[i]<'0' || str[i]>'9') return 0;
			result = result * 10 + str[i] - '0';
		}

		if (!sign) result = -result;
		return result;
	}
};