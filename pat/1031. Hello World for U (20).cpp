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
	string s;
	cin >> s;
	int n = s.size();
	int n1 = 0, n2 = 0;
	for (int i = 0; i < n; i++)
	{//求出n1的最大值
		n1 = i;
		n2 = n + 2 - 2 * n1;
		if (n2 < n1) break;
	}
	if (n2 < n1)
		n1--;
	n2 = n + 2 - 2 * n1;
	string mid = "";
	for (int i = 0; i < n2 - 2; i++)
		mid += " ";

	for (int i = 0; i < n1 - 1; i++)
	{
		cout << s[i] << mid << s[s.size() - 1 - i] << endl;
	}
	for (int i = n1 - 1; i < n1 - 1 + n2; i++)
	{
		cout << s[i];
	}
	cout << endl;
	return 0;
}