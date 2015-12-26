/*
题目：
1.因为C的范围是0到1000，最多有50条等式，所以采用遍历每个数值，看其满足的等式条数，最终取最大值。
2.注意我们遍历的时候，不能直接遍历0，1，2，3，4，5；因为出现等式X > 2和X < 3，X=2.5能够同时满足要求。
3.遍历的时候使用0.5的步进进行判断。

*/
/*

测试用例：

2
X > 2
X < 3
正确答案：
2


6
X = 1
X = 2
X = 3
X > 0
X >= 0
X <= 0
正确答案：
3

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
bool cal(float&x, pair<string, int>&e)
{
	string op = e.first;
	int c = e.second;
	if (op == "<")
		return x < c;
	else if (op == "<=")
		return x <= c;
	else if (op == ">")
		return x > c;
	else if (op == ">=")
		return x >= c;
	else
		return x == c;
	
}
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{

	int n;
	cin >> n;
	vector<pair<string, int>> equation(n);
	string x;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> equation[i].first >> equation[i].second;
	}
	int answer = 0;
	//遍历0到1000
	for (float x = -0.5; x <= 1000.5; x+=0.5)
	{
		int tmp = 0;
		//遍历所有的等式，求出满足的条数
		for (int i = 0; i < n; i++)
		{
			tmp += cal(x, equation[i]);
		}
		answer = max(tmp, answer);
	}
	cout << answer << endl;
	return  0;
}
