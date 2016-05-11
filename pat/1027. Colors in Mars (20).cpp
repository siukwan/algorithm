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
string int2str(int a)
{
	char c;
	if (a >= 0 && a <= 9)
		c = a + '0';
	else
		c = a - 10 + 'A';
	string ans = "";
	ans += c;
	return ans;
}
string dec213(int a)
{
	if (a == 0) return "00";
	string ans = "";
	while (a != 0)
	{
		ans += int2str(a % 13);
		a /= 13;
	}
	for (int i = 0; i < ans.size() / 2; i++)
		swap(ans[i], ans[ans.size() - 1 - i]);
	if (ans.size() == 1) ans = '0' + ans;
	return ans;
}
int main(void)
{
	int r, g, b;
	cin >> r >> g >> b;
	cout << "#" << dec213(r) << dec213(g) << dec213(b) << endl;
	return 0;
}