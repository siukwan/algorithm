/*
一个数如果恰好等于它的各因子(该数本身除外)子和，如：6 = 3 + 2 + 1。则称其为“完数”；若因子之和大于该数，则称其为“盈数”。 求出2到60之间所有“完数”和“盈数”。
输入描述 :

题目没有任何输入。


输出描述 :

输出2到60之间所有“完数”和“盈数”，并以如下形式输出：
E : e1 e2 e3 ......(ei为完数)
G : g1 g2 g3 ......(gi为盈数)
	其中两个数之间要有空格，行尾不加空格。
*/

#include<stdio.h>
#include<set>
#include<vector>
using namespace std;
set<int> getFactor(int n)
{
	set<int> result;
	if (n != 0) result.insert(1);
	for (int i = 2; i*i <= n; ++i)
	{
		if (n%i == 0)
		{
			result.insert(i);
			result.insert(n / i);
		}
	}
	return result;
}

int getSum(set<int> s)
{
	int result = 0;
	for (auto ite = s.begin(); ite != s.end(); ++ite)
		result += *ite;
	return result;
}

int main()
{
	vector<int> table(61, 0);
	for (int i = 2; i < table.size(); ++i)
	{
		int tmp = getSum(getFactor(i));
		if (i != 1 && tmp == i)
			table[i] = 1;
		else if (i != 1 && tmp > i)
			table[i] = 2;
	}
	vector<int> perfect;
	vector<int> more;
	for (int i = 2; i <= 60; ++i)
	{
		if (table[i] == 1)
			perfect.push_back(i);
		else if (table[i] == 2)
			more.push_back(i);
	}
	printf("E:");
	/*E: e1 e2 e3 ......(ei为完数)
	G: g1 g2 g3 ......(gi为盈数)
	*/
	for (size_t i = 0; i < perfect.size(); i++)
	{
		printf(" %d", perfect[i]);
	}
	printf("\nG:");

	for (size_t i = 0; i < more.size(); i++)
	{
		printf(" %d", more[i]);
	}
	return 0;
}