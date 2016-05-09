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

bool isPalindromic(string s)
{
	for (int i = 0; i < s.size() / 2; i++)
	{
		if (s[i] != s[s.size() - 1 - i])
			return false;
	}
	return true;
}
//string reverse(string s)
//{
//  string t = "";
//  int i = 0;
//  for (; i < s.size(); i++)
//  {//去掉开头的0
//      if (s[i] != '0') break;
//  }
//
//  for (; i < s.size(); i++)
//  {
//      t += s[i];
//  }
//  return t;
//}

int main(void)
{
	string s;//以string保存数字
	int k;
	cin >> s >> k;
	int step = 0;
	string t = s;
	while (step < k&&!isPalindromic(t))
	{
		s = t;
		t = "";
		for (int i = 0; i < s.size(); i++)
		{//t为s的翻转
			t = s[i] + t;
		}

		int carry = 0;
		string tmp = "";
		for (int i = s.size() - 1; i >= 0; i--)
		{//进行累加
			int digit = (s[i] - '0') + (t[i] - '0') + carry;
			carry = digit / 10;
			char c = digit % 10 + '0';
			tmp = c + tmp;
		}
		if (carry != 0)
		{//如果有进位，则需要添加
			char c = carry + '0';
			tmp = c + tmp;
		}
		int i = 0;
		for (; i < tmp.size(); i++)
		{//去掉前面的0
			if (tmp[i] != '0') break;
		}
		t = "";
		for (; i < tmp.size(); i++)
			t += tmp[i];//生成最终结果
		step++;
	}
	cout << t << endl << step << endl;

	return 0;
}