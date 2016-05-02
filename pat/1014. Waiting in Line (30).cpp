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
/*
2 1 4 4
599 540 1 2
1 2 3 4
*/
struct customNode{
	int process;//还需要处理多长的时间，每经过一次循环，--
	int cost;//该用户需要处理的时间
	string finished;//完成的时间
	customNode() :process(0), cost(0), finished(""){};
};
string int2str(int a)
{//数字转string
	char b = a / 10 + '0';
	char c = a % 10 + '0';
	string ans = "1";
	ans += b;
	ans += c;
	return ans.substr(1);
}
string recordTime(int a)
{//int转时间
	int hour = a / 60 + 8;
	int min = a % 60;
	string ans = int2str(hour) + ":" + int2str(min);
	//cout << ans << endl;
	return ans;
}
int main(void) {

	int n, m, k, q;//n为银行窗口数，m为每个窗口的黄线内容量，k个客户，q是查询序列
	cin >> n >> m >> k >> q;
	vector<customNode> custom(k);
	for (int i = 0; i < k; i++)
	{//输入用户需要处理的时间
		cin >> custom[i].process;
		custom[i].finished = "";
		custom[i].cost = custom[i].process;//初始化用户需处理的时间
	}

	//窗口队列，每个窗口为一个队列
	vector<queue<int>> window(n);
	int input = 0;
	for (; input < n*m&input < k; input++)
	{//把客户压进窗口的队列
		window[input%n].push(input);
	}

	//10个小时，按照一分钟一分钟地进行计算
	for (int i = 0; i < 599; i++)
	{//一直可以处理到17：59
		bool allFinished = true;//全部处理完毕
		for (int j = 0; j < n; j++)
		{
			if (window[j].empty()) continue;//队列为空意味着等待队列无人了。因为窗口一有位置，就会马上插入等待队列中的人。

			allFinished = false;//窗口中仍有需要处理的用户

			if (i >= 540)
			{//超过17：00的不再接收新的用户处理
				int tmp = window[j].front(); //读取当前窗口的第一个用户
				if (custom[tmp].process == custom[tmp].cost)
				{//如果这些用户还没有被处理，即process==cost，现在已经超过17点，那么直接弹出，不再处理
					while (!window[j].empty())
					{//后面的用户肯定也没有处理，直接弹出
						window[j].pop();
					}
					continue;//该窗口已经为空，直接下一个窗口
				}
			}

			int p = window[j].front();//读取当前窗口的第一个用户
			custom[p].process--;//该用户处理时间减1分钟
			if (custom[p].process == 0)
			{//如果处理时间为0，证明客户处理完毕
				custom[p].finished = recordTime(i + 1);
				window[j].pop();//
				if (input<k&&i<539)
				{//如果input小于k，即仍有人需要服务，并且时间小于17:00，则进行排队处理
					window[j].push(input++);
				}
			}
		}
	}


	for (int i = 0; i < q; i++)
	{//输入查询队列
		int query;
		cin >> query;
		if (custom[query - 1].process != 0)
			cout << "Sorry" << endl;
		else
			cout << custom[query - 1].finished << endl;
	}
	return 0;
}