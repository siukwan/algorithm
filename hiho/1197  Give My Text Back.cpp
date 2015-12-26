/*
题目：
1.主要涉及字符串处理。
2.字母之间只能够是空格或者逗号+空格或者句号+空格隔开。
3.一行里面可能有多个句子，这些句子不用换行，但是需要用句号+空格隔开，并且第一个字母需要大写。

*/
/*

测试用例：
 my Name  is Little   Hi. ami           .i hate      hiho                     ,codr. EEENNN.
   His   name IS Little ho  ,  We are   friends.
 my Name  is Little   Hi.His   name IS Little ho  ,  We are   friends.
my Name  is Little   Hi. His   name IS Little ho  ,  We are   friends.
 His   name IS Little ho  ,We are   friends.   weoifj   ,jo.
Jo, f, j l, o,o, l.

正确答案：
My name is little hi. Ami. I hate hiho, codr. Eeennn.
His name is little ho, we are friends.
My name is little hi. His name is little ho, we are friends.
My name is little hi. His name is little ho, we are friends.
His name is little ho, we are friends. Weoifj, jo.
Jo, f, j l, o, o, l.


*/

#include<string>
#include <iomanip>
#include<fstream>
#include<set>
#include<queue>
#include<map>
//#include<unordered_set>
//#include<unordered_map>
//#include <sstream>
//#include "func.h"
//#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
//#include<stack>
#include<vector>
#include <algorithm>
using namespace std;
char lower(char&c)
{
	if (c <= 'Z'&&c >= 'A') return c - 'A' + 'a';
	else return c;
}

char upper(char&c)
{
	if (c <= 'z'&&c >= 'a') return c - 'a' + 'A';
	else return c;
}
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{

	string str;
	while (getline(cin, str))
	{
		string newStr="";
		bool blank = false;
		bool comma = false;
		bool period = false;
		for (int i = 0; i < str.size(); i++)
		{
			//如果是句子的开头，且str[i]元素不为空
			if (newStr == ""&&str[i]!=' ')
			{
				newStr += upper(str[i]);
			}
			//如果不是句子的开头
			else if (newStr != "")
			{
				//如果是句号
				if (str[i] == '.')
				{//标记之前记录的是句号
					period = true;
					newStr += str[i];
				}
				else if (str[i] == ',')
				{
					comma = true;
					newStr += str[i];
				}
				//标记空白
				else if (str[i]==' ')
					blank = true;
				else
				{
					//如果之前是句号，则这个是新的句子，要加上空白，并且字母要大写
					if (period)
					{
						newStr += ' ';
						newStr += upper(str[i]);
						period = false;
						comma = false;
						blank = false;
					}
					//如果之前是逗号或者是空白，则要加上空白，字母要小写
					else if (comma || blank)
					{
						newStr += ' ';
						newStr += lower(str[i]);
						period = false;
						comma = false;
						blank = false;
					}
					//其他情况，即只是字母，全部小写
					else
						newStr += lower(str[i]);
				}

			}
		}
		cout << newStr << endl;
	}
	return  0;
}
