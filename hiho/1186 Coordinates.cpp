
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
//#include "siukwanAlloctor.h"
using namespace std;

int main()
{

	int p, q;
	scanf("%d%d", &p, &q);
	set<int>pd, qd;
	int n = sqrt(max(p, q));
	for (int i = 1; i <= n; ++i)
	{
		if (p >= i && p%i == 0)
		{
			pd.insert(i);
			pd.insert(p / i);
		}
		if (q >= i && q%i == 0)
		{
			qd.insert(i);
			qd.insert(q / i);
		}
	}

	for (set<int>::iterator ite = pd.begin(); ite != pd.end(); ++ite)
	{
		for (set<int>::iterator ite2 = qd.begin(); ite2 != qd.end(); ++ite2)
		{
			printf("%d %d\n", *ite, *ite2);
		}
	}

	return 0;
}