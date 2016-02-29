/*
题目描述

利用字符重复出现的次数，编写一个方法，实现基本的字符串压缩功能。比如，字符串“aabcccccaaa”经压缩会变成“a2b1c5a3”。若压缩后的字符串没有变短，则返回原先的字符串。
给定一个string iniString为待压缩的串(长度小于等于3000)，保证串内字符均由大小写英文字母组成，返回一个string，为所求的压缩后或未变化的串。
测试样例
"aabcccccaaa"
返回："a2b1c5a3"
"welcometonowcoderrrrr"
返回："welcometonowcoderrrrr"

*/
class Zipper {
public:
	string zipString(string iniString) {
		// write code here
		if (iniString == "") return "";
		iniString += " ";
		string result = "";
		char c = iniString[0];
		int count = 1;
		for (int i = 1; i<iniString.size(); ++i)
		{
			if (c != iniString[i])
			{
				result += c;
				result += int2str(count);
				c = iniString[i];
				count = 1;
			}
			else
				count++;
		}
		iniString = iniString.substr(0, iniString.size() - 1);
		if (iniString.size() < result.size())
			result = iniString;
		return result;
	}
	string int2str(int a)
	{
		if (a == 0) return "";
		string result = "";
		while (a != 0)
		{
			char c = a % 10 + '0';
			result = c + result;
			a = a / 10;
		}
		return result;
	}
};