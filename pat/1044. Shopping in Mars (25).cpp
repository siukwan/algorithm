#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <map>
#include <set>
#include "limits.h"
using namespace std;

/*
16 15
3 2 1 5 4 6 8 7 16 10 15 11 9 12 14 13

5 13
2 4 5 7 9

10 1
2 3 4 5 6 1 2 3 4 6

10 1
2 3 4 5 1 1 2 1 1 1
ans：
5-5
6-6
8-8
9-9
10-10

10 0
2 3 4 5 1 1 2 1 1 1
ans：
5-5
6-6
8-8
9-9
10-10

10 -1
2 3 4 5 1 1 2 1 1 1
ans：
5-5
6-6
8-8
9-9
10-10
*/
bool cmp(const pair<int, pair<int, int>>&a, const pair<int, pair<int, int>>&b)
{
	if (a.first<b.first)
		return true;
	else if (a.first == b.first&&a.second.first<b.second.first)
		return true;
	else return false;
}
int main(void)
{
	int sum, pay;
	scanf("%d %d", &sum, &pay);
	vector<int> diamonds(sum);
	for (int i = 0; i<sum; i++)
	{
		scanf("%d", &diamonds[i]);
	}
	int i = 0, j = 0;
	int value = diamonds[0];//默认输入的数组大于0
	int minAns = INT_MAX;
	vector<pair<int, pair<int, int>>> ans(0);
	while (1)
	{
		if (value == pay&&i <= j)
		{//加入i<=j，避免出现2-1，6-4之类的，j小于i的情况
			minAns = min(minAns, value);
			ans.push_back({ value, { i + 1, j + 1 } });
			value -= diamonds[i++];
		}
		else if (value>pay&&i <= j)
		{//加入i<=j，避免出现2-1，6-4之类的，j小于i的情况
			if (value <= minAns)
			{//value>pay && value<=minAns,所以 pay<value<=minAns,minAns>pay
				minAns = value;
				ans.push_back({ value, { i + 1, j + 1 } });
			}
			value -= diamonds[i++];

		}
		else//value<pay
		{
			j++;
			if (j<diamonds.size())
				value += diamonds[j];
			else
				break;
		}
	}
	sort(ans.begin(), ans.end(), cmp);
	for (int k = 0; k<ans.size(); k++)
	{
		if (ans[k].first == minAns)
			printf("%d-%d\n", ans[k].second.first, ans[k].second.second);
		else break;
	}


	return 0;
}