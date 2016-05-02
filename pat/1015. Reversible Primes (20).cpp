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
87767

*/
int main(void)
{
	vector<bool> prime(660000, true);
	prime[0] = false;
	prime[1] = false;
	prime[2] = true;
	for (int i = 2; i < 660000; i++)
	{
		if (prime[i])
		{
			for (int j = 2; j*i < 660000; j++)
			{
				prime[j*i] = false;
			}
		}
	}

	int n, d;
	while (scanf("%d", &n) != EOF)
	{
		if (n < 0) return 0;//以负数结束
		cin >> d;
		int num = n;
		string s = "";
		while (num != 0)
		{//求余，把它转化为d进制格式的数，但求出来的string刚好是反的
			char c = num%d + '0';
			s += c;
			num /= d;
		}
		//for (int i = 0; i < s.size() / 2; i++)
		//  swap(s[i], s[s.size() - 1 - i]);
		int reverse = 0;
		for (int i = 0; i < s.size(); i++)
		{
			reverse = (s[i] - '0') + reverse * d;
		}
		if (prime[n] && prime[reverse]) cout << "Yes" << endl;
		else cout << "No" << endl;
	}

	return 0;
}