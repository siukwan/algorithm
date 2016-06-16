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
2
36 52 37 38 3 39 40 53 54 41 11 12 13 42 43 44 2 4 23 24 25 26 27 6 7 8 48 49 50 51 9 10 14 15 16 5 17 18 19 1 20 21 22 28 29 30 31 32 33 34 35 45 46 47
3
36 52 37 38 3 39 40 53 54 41 11 12 13 42 43 44 2 4 23 24 25 26 27 6 7 8 48 49 50 51 9 10 14 15 16 5 17 18 19 1 20 21 22 28 29 30 31 32 33 34 35 45 46 47

1
14 15 16 17 18 19 20 21 22 23 24 25 26 1 2 3 4 5 6 7 8 9 10 11 12 13 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54
*/
string int2Card(int a)
{
	string ans = "";
	int pic = a / 13;
	if (pic == 0)ans = "S";
	else if (pic == 1) ans = "H";
	else if (pic == 2) ans = "C";
	else if (pic == 3) ans = "D";
	else if (pic == 4) ans = "J";
	if (a % 13 >= 9)
	{
		ans += '1';
		char c = (a % 13 - 9) + '0';
		ans += c;
	}
	else
	{
		char c = a % 13 + '1';
		ans += c;
	}
	return ans;
}
int main(void)
{
	//for (int i = 0; i < 54; i++)
	//{
	//  cout << ",\"" << int2Card(i)<<"\"";
	//}
	int repeatTime;
	cin >> repeatTime;
	vector<int> shuffling(54);
	vector<string> original = { "S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10", "S11", "S12", "S13", "H1", "H2",
		"H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10", "H11", "H12", "H13", "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "C11", "C12", "C13", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "D11", "D12", "D13", "J1", "J2" };
	vector<string> num(54);
	for (int i = 0; i<54; i++)
	{
		cin >> shuffling[i];
		shuffling[i]--;
		num[i] = i;// initial the shuffling vector
	}


	for (int i = 0; i<repeatTime; i++)
	{
		for (int j = 0; j<54; j++)
		{//把j号卡放在shuffling[j]的位置
			num[shuffling[j]] = original[j];
		}
		original = num;
	}

	for (int i = 0; i<54; i++)
	{
		cout << original[i];
		if (i != 53) cout << " ";
	}
	return 0;
}