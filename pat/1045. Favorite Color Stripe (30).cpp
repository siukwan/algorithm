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
/*
6
5 2 3 1 5 6
12 2 2 4 1 5 5 6 3 1 1 5 6

6
5 2 3 1 5 6
10 2 2 3 1 3 1 3 1 3 1

6
5 2 3 1 5 6
10
5 6 6 6 6 6 6 6 6 6 6

6
5 2 3 1 5 6
10
2 6 6 6 6 6 6 6 6 6 6


6
5 2 3 1 5 6
10
2 2 2 6 6 6 6 6 6 6 6

6
5 2 3 1 5 6
10
2 2 2 6 6 6 6 5 6 6 6

6
5 2 3 1 5 6
10
2 2 2 6 6 6 6 6 5 6 6
*/
int main(void)
{
	int colourSum, fnum, onum;
	cin >> colourSum >> fnum;
	vector<int> f(fnum);
	for (int i = 0; i<fnum; i++)
	{
		scanf("%d", &f[i]);
	}
	cin >> onum;
	vector<int> o(onum);

	for (int i = 0; i<onum; i++)
	{
		scanf("%d", &o[i]);
	}

	vector<vector<int>> dp(fnum + 1, vector<int>(onum + 1, 0));

	int thisMax = 0;
	for (int i = 1; i <= f.size(); i++)
	{
		for (int j = 1; j <= o.size(); j++)
		{
			dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
			if (f[i - 1] == o[j - 1])
				dp[i][j]++;
		}
	}
	cout << dp[fnum][onum] << endl;
	return 0;
}