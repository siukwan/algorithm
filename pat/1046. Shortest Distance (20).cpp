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

int main(void)
{

	int n;
	scanf("%d", &n);
	int *num = new int[n];
	int *dp = new int[n];
	memset(dp, 0, sizeof(dp));
	int sum = 0;
	for (int i = 0; i<n; i++)
	{
		scanf("%d", &num[i]);
		if (i == 0) dp[i] = num[i];
		else dp[i] = dp[i - 1] + num[i];
		sum += num[i];
	}
	int m;
	scanf("%d", &m);
	for (int i = 0; i<m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		if (a>b) swap(a, b);
		int tmp = dp[b - 1] - dp[a - 1] + num[a - 1] - num[b - 1];
		int tmp2 = sum - tmp;
		printf("%d\n", min(tmp2, tmp));
	}
	return 0;
}