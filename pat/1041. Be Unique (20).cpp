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

int main(void)
{

	int *frequency = new int[100001];
	memset(frequency, 0, 100001 * sizeof(int));
	int sum;
	cin >> sum;
	int *num = new int[sum];
	for (int i = 0; i<sum; i++)
	{
		scanf("%d", &num[i]);
		frequency[num[i]]++;
	}
	for (int i = 0; i<sum; i++)
	{
		if (frequency[num[i]] == 1)
		{
			cout << num[i] << endl;
			return 0;
		}
	}
	cout << "None" << endl;
	return 0;
}