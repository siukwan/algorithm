/*
题目：
1.p和q都不大，直接遍历求出所有的因数。
2.原计划遍历到p/2或者q/2的，但是发现当p==1或者q==1时，会直接跳出没有遍历，于是直接改为遍历到p或q。

*/
/*

测试用例：

1 1
正确答案：
1 1

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

/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{

	int p, q;
	cin >> p>>q;
	set<int> pDivisors;
	set<int> qDivisors;
	//求出所有的因数
	for (int i = 1; i <= max(p, q); i++)
	{
		if (p%i == 0)
		{
			pDivisors.insert(i);
			pDivisors.insert(p / i);
		}
		if (q%i == 0)
		{
			qDivisors.insert(i);
			qDivisors.insert(q / i);
		}
	}

	//进行输出
	vector<int> qDiv(qDivisors.size(), 0); 
	int i = 0;
	for (set<int>::iterator ite = qDivisors.begin(); ite != qDivisors.end(); ite++,i++)
	{
		qDiv[i] = *ite;
	}

	for (set<int>::iterator ite = pDivisors.begin(); ite != pDivisors.end(); ite++)
	{
		for (int j = 0; j < qDiv.size(); j++)
		{
			printf("%d %d\n", *ite, qDiv[j]);
		}
	}

	return  0;
}
