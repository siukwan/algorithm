#include<vector>
#include <algorithm>
//#include<stack>
#include<set>
#include<queue>
#include<map>
//#include<unordered_set>
#include<unordered_map>
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

	string  str;
	getline(cin, str);
	int maxLen = 0;
	for (int i = 0; i<str.size(); i++)
	{
		int oddLen = 1, evenLen = 0;
		for (int j = 1; i - j >= 0 && i + j<str.size(); j++)
		{
			if (str[i + j] == str[i - j])
				oddLen += 2;
			else break;
		}
		for (int j = 0; i - j >= 0 && i + j + 1<str.size(); j++)
		{
			if (str[i + j + 1] == str[i - j])
				evenLen += 2;
			else break;
		}
		maxLen = max(maxLen, max(oddLen, evenLen));
	}
	cout << maxLen << endl;
	return 0;
}
