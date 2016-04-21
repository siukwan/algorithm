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
	int n;
	while (scanf("%d", &n) != EOF)
	{
		int *request = new int[n + 1];
		request[0] = 0;
		int sum = n * 5;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &request[i]);
			int diff = request[i] - request[i - 1];
			if (diff < 0) sum += -diff * 4;//注意是负号
			else sum += diff * 6;
		}
		cout << sum << endl;
	}
	return 0;
}