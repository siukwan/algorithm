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
int time2Int(string s)
{
	int hour = (s[0] - '0') * 10 + s[1] - '0';
	int min = (s[3] - '0') * 10 + s[4] - '0';
	int sec = (s[6] - '0') * 10 + s[7] - '0';
	return hour * 3600 + min * 60 + sec;
}
struct people{
	int begin, end;
	string ID;
	people() :begin(0), end(0), ID(""){};
};
bool cmpBegin(const people&a, const people&b)
{
	if (a.begin < b.begin) return true;
	else return false;
}
bool cmpEnd(const people&a, const people&b)
{
	if (a.end > b.end) return true;
	else return false;
}
int main(void) {

	int n;
	cin >> n;
	vector<people> p(n);
	for (int i = 0; i < n; i++)
	{
		string a, b, c;
		cin >> a >> b >> c;
		p[i].ID = a;
		p[i].begin = time2Int(b);
		p[i].end = time2Int(c);
	}
	string first = "";
	sort(p.begin(), p.end(), cmpBegin);
	first = p[0].ID;
	sort(p.begin(), p.end(), cmpEnd);
	string last = p[0].ID;
	cout << first << " " << last << endl;
	return 0;
}