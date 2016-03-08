/*
NowCoder最近在研究一个数列：
* F(0) = 7
* F(1) = 11
* F(n) = F(n-1) + F(n-2) (n≥2)
他称之为NowCoder数列。请你帮忙确认一下数列中第n个数是否是3的倍数。

输入描述:

输入包含多组数据。
每组数据包含一个整数n，(0≤n≤1000000)。


输出描述:

对应每一组输入有一行输出。

如果F(n)是3的倍数，则输出“Yes”；否则输出“No”。

输入例子:

0
1
2
3
4
5

输出例子:

No
No
Yes
No
No
No

*/

// write your code here cpp
#include<stdio.h>
using namespace std;

int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		if (n % 4 == 2)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}