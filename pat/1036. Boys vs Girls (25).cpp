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
struct studentNode{
	string name;
	string id;
	int grade;
	studentNode(string n, string i, int g) :name(n), id(i), grade(g){};
	studentNode() :name(""), id(""), grade(0){};
};
bool cmpM(const studentNode&a, const studentNode&b)
{
	return a.grade < b.grade;
}
bool cmpF(const studentNode&a, const studentNode&b)
{
	return a.grade > b.grade;
}
int main(void)
{
	int n;
	cin >> n;
	vector<studentNode> m(0);
	vector<studentNode> f(0);
	for (int i = 0; i < n; i++)
	{
		string name, id, gender;
		int grade;
		cin >> name >> gender >> id >> grade;
		if (gender == "F")
			f.push_back(studentNode(name, id, grade));
		else
			m.push_back(studentNode(name, id, grade));
	}
	sort(f.begin(), f.end(), cmpF);
	sort(m.begin(), m.end(), cmpM);

	if (f.size()>0)
		cout << f[0].name << " " << f[0].id << endl;
	else
		cout << "Absent" << endl;
	if (m.size()>0)
		cout << m[0].name << " " << m[0].id << endl;
	else
		cout << "Absent" << endl;
	if (f.size() > 0 && m.size() > 0)
		cout << f[0].grade - m[0].grade << endl;
	else
		cout << "NA" << endl;



	return 0;
}