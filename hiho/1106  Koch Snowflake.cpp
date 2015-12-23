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
1.题目主要是给出了科赫雪花分形，给出变形的代数n和边的编号i，求出这条边属于第几代。

2.首先我们来看看从第n-1代到第n代的变化，设第n-1代中的边i，如下图：

                      4(i-1)+2    4(i-1)+3
                              /\
     i            4(i-1)+1   /  \   4(i-1)+4
----------              -----    ------
  第n-1代                   第n代   

我们看到，在第n-1代中的边i，变形到第n代时，会演化成为4(i-1)+1、4(i-1)+2、4(i-1)+3、4(i-1)+4.

其中4(i-1)+2和4(i-1)+3是第n代的边，而4(i-1)+1、4(i-1)+4是第n-1代的边。

那么现在我们明确了，如果某边的编号i%4==2或==3，那么这条边就是第n代的，否则，返回到上一代中继续求。
返回到上一代时，4(i-1)+1、4(i-1)+4对应的是i，那么假设边k需要返回到上一代，那么应该k/4向上取整（例如1/4=1,4/4=1），然后继续迭代。

*/
int dfs(int side, int generation)
{
	if (generation == 0)
		return 0;
	else
	{
		if (side % 4 == 2 || side % 4 == 3)
			return generation;
		else
		{
			int i = side / 4;
			if (side % 4) i++;
			return dfs(i, generation - 1);
		}
	}
}
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int n;
	cin >> n;
	while (n--)
	{
		int side, generation;
		cin >> side >> generation;
		cout << dfs(side, generation) << endl;
	}
	return  0;
}
