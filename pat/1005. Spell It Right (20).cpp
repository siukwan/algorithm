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
using namespace std;

int main(void) {

	string str;
	cin >> str;
	int sum = 0;
	for (int i = 0; i < str.size(); i++)
	{
		sum += str[i] - '0';//直接进行各位的累加
	}
	string int2Str[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	str = "";
	string ans = "";
	if (sum == 0) ans = "zero";
	while (sum != 0)
	{
		char c = sum % 10 + '0';
		str = c + str;
		sum /= 10;
	}
	for (int i = 0; i < str.size(); i++)
	{
		ans += int2Str[str[i] - '0'];
		if (i != str.size() - 1)
			ans += " ";
	}
	cout << ans << endl;


	return 0;
}