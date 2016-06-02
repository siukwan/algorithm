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
bool cmp(const int&a, const int&b)
{
	return a > b;
}
int main(void)
{
	int n;

	vector<int> couponP(0);
	vector<int> couponN(0);
	vector<int> productP(0);
	vector<int> productN(0);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a;
		scanf("%d", &a);
		if (a < 0) couponN.push_back(a);
		else couponP.push_back(a);
	}

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a;
		scanf("%d", &a);
		if (a < 0) productN.push_back(a);
		else productP.push_back(a);
	}
	sort(couponP.begin(), couponP.end(), cmp);
	sort(couponN.begin(), couponN.end());
	sort(productP.begin(), productP.end(), cmp);
	sort(productN.begin(), productN.end());
	int sum = 0;
	for (int i = 0; i < couponP.size() && i < productP.size(); i++)
		sum += couponP[i] * productP[i];
	for (int i = 0; i < couponN.size() && i < productN.size(); i++)
		sum += couponN[i] * productN[i];
	cout << sum << endl;
	return 0;
}