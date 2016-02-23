/*
题目描述

请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。

*/
class Solution {
public:
	bool isNumeric(char* string)
	{
		std::string s = "";

		int pos = 0;
		while (string[pos] != 0)
		{
			if (string[pos] == 'E')
			{
				s += 'e';
				pos++;
			}
			else s += string[pos++];
		}

		if (s.size() == 0)
			return false;
		while (s[0] == ' ')
		{//去除开头的空格
			if (s.size() == 1) return false;
			s = s.substr(1);
		}

		while (s[s.size() - 1] == ' ')
		{//去除尾部的空格
			s = s.substr(0, s.size() - 1);
		}

		if (s == ".") return false;
		bool sign = false;
		if (s[0] == '+' || s[0] == '-')
		{
			if (s.size() == 1) return false;//如果单纯只有一个符号，则false
			s = s.substr(1);//把前面的符号截掉
			sign = true;
		}
		if (s == ".") return false;

		int dot_pos = INT_MAX;//小数点标志位
		int e_pos = INT_MAX;//e的位置
		int sign_pos = INT_MAX;//e后面的符号标志位,可以为+或-
		for (int i = 0; i<s.size(); i++)
		{
			if (s[i] == '.')
			{//存在小数点
				if (dot_pos != INT_MAX || i>e_pos)
					return false;//如果已经存在一个小数点，或者小数点的位置在e的后面，false
				else
					dot_pos = i;
			}
			else if (s[i] == '+' || s[i] == '-')
			{
				if (sign_pos != INT_MAX || i != (e_pos + 1)/*||i<e_pos || e_pos==INT_MAX */)
					return false;//已存在符号位或者，符号位在e的前面。符号位必须紧接着e
				else
					sign_pos = i;
			}
			else if (s[i] == 'e')
			{
				if (e_pos != INT_MAX)
					return false;
				else
					e_pos = i;
			}
			else if (s[i]<'0' || s[i]>'9')
				return false;
		}

		//对e进行处理，可能存在符号也可能不存在
		if (e_pos != INT_MAX)
		{
			if (e_pos == 0) return false;//e在开头 
			std::string str_e = s.substr(e_pos + 1);
			if (sign_pos != INT_MAX) str_e = str_e.substr(1);//截掉符号
			if (str_e == "") return false;//避免出现e结尾的 例如10e
			int int_tmp = str2int(str_e);
			s = s.substr(0, e_pos);//截去e部分
		}

		//先截取，进行整数部分判断
		std::string str_n = s;//整数部分
		int int_n;
		if (dot_pos != INT_MAX)
		{
			str_n = s.substr(0, dot_pos);
		}
		if (str_n != "")//避免 .1 这个小数点开头的情况
		{
			int_n = str2int(str_n);

			//整数部分为0，且不存在小数部分，但存在e，false
			//if(int_n==0&&dot_pos==INT_MAX && e_pos!=INT_MAX) return false;
		}
		else int_n = 0;

		//判断小数部分
		if (dot_pos != INT_MAX)
		{
			std::string str_dot = s.substr(dot_pos + 1);
			int int_dot = str2int(str_dot);
			if (int_n == 0 && int_dot == 0 && e_pos != INT_MAX) return false;//整数和小数部分同时为0，报错
		}
		return true;
	}
	int str2int(std::string s)
	{
		int ret = 0;
		for (int i = 0; i<s.size(); i++)
		{
			ret = ret * 10 + s[i] - '0';
		}
		return ret;
	}
	std::string int2str(int n)
	{
		if (n == 0) return "0";
		std::string ret = "";

		while (n != 0)
		{
			int tmp = n % 10;
			char c = tmp + '0';
			n = n / 10;
			ret = c + ret;
		}
		return ret;
	}
};