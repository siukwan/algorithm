
#include<stdio.h>
#include<iostream>
#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
#include<set>
#include<queue>
//#include<map>
//#include<unordered_set>
//#include<unordered_map>
#include <sstream>
//#include "func.h"
//#include <list>
using namespace std;

int main(void)
{
	int T;
	cin >> T;
	while (T--)
	{
		string s, t;
		cin >> s >> t;
		vector<int> next(s.size() + 1, 0);
		next[0] = next[1] = 0;
		for (int i = 1; i<s.size(); ++i){

			//循环实质是求next[i+1]的值，所以一直比较i+1的前一个元素即i，找到与s[i]相等的s[next[j]]，然后next[i+1]=next[j+1]

			int j = next[i];
			while (j>0 && s[i] != s[j]){//如果j>0，且s[i]与s[j]不相等，如果j为0，证明还没开始匹配模版
				j = next[j];
			}
			if (s[i] == s[j])//如果s[i][j]相等，则next[i+1]为j+1
				next[i + 1] = j + 1;
		}
		int ans = 0;
		for (int i = ans = 0, j = 0; i<t.size(); ++i){

			while (j>0 && t[i] != s[j])
			{
				j = next[j];
			}
			//跳出循环只有两种情况，一种是j==0，另外一种是t[i]==s[j]
			//对于第二种情况，我们可以j++，从而下次循环判断t[i+1]=s[j+1]
			//对于第一种情况，即需要从头开始寻找模式串
			if (s[j] == t[i])
				j++;
			if (j == s.size())
			{
				ans++;
				j = next[j];//next数组的size比s.size()大1
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}
