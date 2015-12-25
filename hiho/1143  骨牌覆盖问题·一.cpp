/*
题目：
首先，这道题目是一道斐波那契数列的题目。
我们来分析一下，第三个图形是如何由前两个图形组成。
 ______           _______
|    | |   或    |  |____|  
|____|_|         |__|____|
扩展到第n个图形，我们有：
 _____________           ______________
|           | |  或     |         |____|  
|___________|_|         |_________|____|
所以，f(n)=f(n-1)+f(n-2)

由于n可能会很大，所以我们需要一些计算的技巧。
斐波那契数列是可以由矩阵计算得到，如下：

[a,b]* [0,1] = [b,a+b]
       [1,1]

令mat =[0,1]
       [1,1]

那么，理论上，我们乘以n个矩阵mat，就可以求得f(n)，
但是n个矩阵相乘，时间复杂度为O(n)，
这时候，我们采用快速幂运算来求解，可以把时间复杂度降为O(logn)。

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
#define MOD 19999997
class matrix22{
public:
	long long a1, a2;
	long long  b1, b2;
	matrix22() :a1(0), a2(1), b1(1), b2(1){};
	matrix22 operator*(const matrix22 tmp)
	{
		matrix22 mat;
		mat.a1 = (a1%MOD)*(tmp.a1%MOD) + (a2%MOD)*(tmp.b1%MOD);
		mat.a2 = (a1%MOD)*(tmp.a2%MOD) + (a2%MOD)*(tmp.b2%MOD);
		mat.b1 = (b1%MOD)*(tmp.a1%MOD) + (b2%MOD)*(tmp.b1%MOD);
		mat.b2 = (b1%MOD)*(tmp.a2%MOD) + (b2%MOD)*(tmp.b2%MOD);
		return mat;
	}
};
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int n;
	scanf("%d", &n);
	int dp1 = 1;
	int dp2 = 2;
	if (n <= 0) printf("0\n");
	else if (n == 1) printf("1\n");
	else if (n == 2) printf("2\n");
	else
	{
		n -= 3;
		matrix22 mat;
		matrix22 ans;
		while (n != 0)
		{
			//如果二进制该位为1，则ans*mat
			if (n & 1)
				ans = ans*mat;
			//mat每次与自身相乘，求得矩阵的1，2，4，8，16次方
			mat = mat*mat;
			n = (n >> 1);
		}
		//输出f(n)
		long long answer =( ans.a2 + 2 * ans.b2)%MOD;
		cout << answer << endl;

	}
	return  0;
}
