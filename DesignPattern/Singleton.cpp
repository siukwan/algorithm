
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
#include<bitset>
using namespace std;

class Singleton
{

public:
	static Singleton* GetInstance()
	{
		if (instance == NULL)
			instance = new Singleton();

		return instance;
	}

private:
	Singleton(){};
	static Singleton* instance;
};
//C++单例模式需要先创建instance
Singleton* Singleton::instance = new Singleton();

int main(void)
{
	Singleton*s1 = Singleton::GetInstance();
	Singleton*s2 = Singleton::GetInstance();

	if (s1 == s2)
		cout << "it's same!" << endl;
	return 0;


}