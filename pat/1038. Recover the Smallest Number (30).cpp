#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <memory.h>
#include "limits.h"
using namespace std;

bool cmp(const string&a, const string&b)
{
	//如果a和b，是前缀关系是，要比较a＋b与b+a的大小
	if (a.size()<b.size() && a == b.substr(0, a.size()))
		return a + b<b + a;
	else if (b.size()<a.size() && b == a.substr(0, b.size()))
		return a + b<b + a;
	else return a<b;
}
/*
5 32 321 3214 0229 87
4 11 122 12 10
4  122 12 10 11
*/

int main(void)
{
	int n;
	cin >> n;
	vector<string> str(n);
	for (int i = 0; i<n; i++)
	{
		cin >> str[i];
	}
	sort(str.begin(), str.end(), cmp);
	string ans = "";
	for (int i = 0; i<n; i++)
	{
		ans += str[i];
	}
	int i = 0;
	while (ans[i] == '0')
	{
		i++;
	}
	//注意全为0的状态
	if (ans.substr(i) == "") cout << 0 << endl;
	else cout << ans.substr(i) << endl;
	return 0;
}