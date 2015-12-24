//#include<string>
//#include <iomanip>
#include<fstream>
//#include<set>
//#include<queue>
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
根据题意，使用普通的遍历操作
*/
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int n;
	scanf("%d", &n);
	vector<int> weight(n, 0);
	for (int i = 0; i < n;i++)
	{
		scanf("%d", &weight[i]);
	}

	int queryN;
	scanf("%d", &queryN);
	while (queryN--)
	{
		int operation;
		int a, b;
		scanf("%d %d %d",&operation, &a, &b);
		//进行修改操作
		if (operation == 1)
			weight[a - 1] = b;
		else
		{//进行查询操作
			int result = INT_MAX;
			for (int i = a - 1; i < b; i++)
				result = min(weight[i], result);
			printf("%d\n", result);
		}
	}

	return  0;
}
