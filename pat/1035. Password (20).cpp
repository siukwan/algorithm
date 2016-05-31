//#include<string>
//#include <iomanip>
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

char replace(char a)
{
	switch (a)
	{
	case'1':return '@';
	case'0':return '%';
	case'l':return 'L';
	case'O':return 'o';
	default:return a;
	}
}

int main(void)
{
	int n;
	cin >> n;
	vector<pair<string, string>> ans(0);
	for (int i = 0; i < n; i++)
	{
		string name, pw;
		cin >> name >> pw;
		bool re = false;
		for (int i = 0; i < pw.size(); i++)
		{
			if (pw[i] == '1' || pw[i] == '0' || pw[i] == 'l' || pw[i] == 'O')
			{
				pw[i] = replace(pw[i]);
				re = true;
			}
		}
		if (re)
		{
			ans.push_back({ name, pw });
		}
	}
	if (ans.size() == 0)
	{
		if (n <= 1)
			printf("There is %d account and no account is modified\n", n);
		else
			printf("There are %d accounts and no account is modified\n", n);

	}
	else
	{
		cout << ans.size() << endl;
		for (int i = 0; i < ans.size(); i++)
			cout << ans[i].first << " " << ans[i].second << endl;
	}
	return 0;
}