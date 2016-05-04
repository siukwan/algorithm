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
int c2int(char c)
{//字符转数字
	if (c <= '9'&&c >= '0')
		return c - '0';
	else if (c <= 'z'&&c >= 'a')
		return c - 'a' + 10;
	else return 0;
}
int main(void) {

	string n1, n2;
	int tag;
	unsigned long long radix;
	cin >> n1 >> n2 >> tag >> radix;
	string s, t;
	if (tag == 1)
	{//tag为1，则radix是n1的进制数
		s = n1;
		t = n2;
	}
	else if (tag == 2)
	{//tag为2，则radix是n2的进制数
		s = n2;
		t = n1;
	}

	unsigned long long sInt = 0;
	for (int i = 0; i < s.size(); i++)
	{//把s转为十进制
		sInt = sInt*radix + c2int(s[i]);
	}

	unsigned long long minRadix = 2;
	for (int i = 0; i < t.size(); i++)
	{//求出最小的进制数
		minRadix = max(minRadix, (unsigned long long)(c2int(t[i]) + 1));
	}
	bool flag = false;
	unsigned long long result = 0;
	unsigned long long r = sInt + 1;//必须+1
	unsigned long long l = minRadix;
	//使用二分法去查找合适的radix
	while (l <= r)//必须要有等号！！
	{//从最小的进制数开始遍历
		unsigned long long j = (l + r) / 2;//没说明j最大是36进制
		unsigned long long tInt = 0;
		for (int i = 0; i < t.size(); i++)
		{//j为t的进制数，求出t在j进制下的十进制大小
			tInt = tInt*j + c2int(t[i]);
			if (tInt > sInt)
			{//如果尚未统计完，tInt就被sInt大，没必要再统计下去
				//说明j进制使得tInt>sInt,t的进制数要比j小
				break;
			}
		}
		if (tInt == sInt)
		{
			flag = true;
			result = j;
			break;
		}
		else if (tInt > sInt)
		{
			r = j - 1;
			/*flag = false;
			break;*/
		}
		else l = j + 1;
	}
	if (flag) cout << result << endl;
	else cout << "Impossible" << endl;


	return 0;
}