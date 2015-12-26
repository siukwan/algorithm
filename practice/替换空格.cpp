/*
替换空格

题目描述

请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
*/
class Solution {
public:
	void replaceSpace(char *str, int length) {
		//计算空格个数
		int spaceCount = 0;
		for (int i = 0; i<length; i++)
		{
			if (*(str + i) == ' ')
				spaceCount++;
		}
		//计算出新的长度
		int newLen = length + 2 * spaceCount;
		char *newStr = new char[newLen];
		char *tmpStr;
		tmpStr = newStr;
		for (int i = 0; i<length; i++)
		{
			//遇到空格就替换程%20
			if (*(str + i) == ' ')
			{
				*(tmpStr) = '%'; tmpStr++;
				*(tmpStr) = '2'; tmpStr++;
				*(tmpStr) = '0'; tmpStr++;
			}
			else
			{
				*tmpStr = *(str + i); tmpStr++;
			}
		}
		tmpStr = 0;

		//把新string的值复制到str，注意结尾
		for (int i = 0; i < newLen; i++)
		{
			*(str + i) = *(newStr + i);
		}
		*(str + newLen) = 0;
	}
};