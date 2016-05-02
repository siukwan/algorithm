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
int main(void)
{
	long long number, radix;
	cin >> number >> radix;
	vector<int> base(0);
	if (number == 0) base.push_back(0);
	while (number != 0)
	{
		//余数很有可能超过char的范围，例如999%1000=999
		base.push_back(number%radix);
		number /= radix;
	}
	bool ans = true;
	for (int i = 0; i < base.size() / 2; i++)
	{
		if (ans && base[i] != base[base.size() - 1 - i])//判断回文
			ans = false;
		swap(base[i], base[base.size() - 1 - i]);//求出来的底数是倒序的，顺便把顺序调整过来
	}
	if (ans)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	for (int i = 0; i < base.size(); i++)
	{
		cout << base[i];
		if (i != base.size() - 1)
			cout << " ";
	}
	cout << endl;

	return 0;
}