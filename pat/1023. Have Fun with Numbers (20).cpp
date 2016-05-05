//#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
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
using namespace std;
/*
3
0011111
The Testing Book
Yue Chen
test code debug sort keywords

2011
3333333
Another Testing Book
Yue Chen
test code sort keywords
ZUCS Print2
2012
2222222
The Testing Book
CYLL
keywords debug book
ZUCS Print2
2011
6
1: The Testing Book
2: Yue Chen
3: keywords
4:
5: 2011
3: blablabla

*/
int str2int(string s)
{
	int a = 0;
	for (int i = 0; i < s.size(); i++)
	{
		a = s[i] - '0' + a * 10;
	}
	return a;
}
int main(void)
{
	string s;
	cin >> s;//采用string记录数字
	string t = "";
	int carry = 0;
	bool ans = true;
	for (int i = s.size() - 1; i >= 0; i--)
	{//对数字乘以2，计算出一个新的string
		int digit = (s[i] - '0') * 2 + carry;
		carry = digit / 10;
		char c = digit % 10 + '0';
		t = c + t;
	}
	if (carry != 0)
	{//判断最后有没有进位
		ans = false;
		char c = carry + '0';
		t = c + t;
	}
	if (ans)
	{
		int digit[10] = { 0 };
		for (int i = 0; i < s.size(); i++)
		{//判断各个数出现的次数
			digit[s[i] - '0']++;
			digit[t[i] - '0']--;
		}
		for (int i = 0; i < 10; i++)
		{//如果s和t的数字出现次数不等，则不合要求
			if (digit[i] != 0) ans = false;
		}
	}
	if (ans) cout << "Yes" << endl;
	else cout << "No" << endl;
	cout << t << endl;
	return 0;
}