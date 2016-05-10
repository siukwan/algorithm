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
#define maxServe 46810
/*
//正常的检测例子，全部为普通玩家
9
20:52:00 10 0
08:00:00 20 0
08:02:00 30 0
20:51:00 10 0
08:10:29 5 0
08:12:00 10 0
20:50:00 10 0
08:01:30 15 0
20:53:00 10 0
3 1
2
答案为：
08:00:00 08:00:00 0
08:01:30 08:01:30 0
08:02:00 08:02:00 0
08:10:29 08:16:30 6
08:12:00 08:20:00 8
20:50:00 20:50:00 0
20:51:00 20:51:00 0
20:52:00 20:52:00 0
3 3 2

//正常的测试例子，没有vip table
9
20:52:00 10 0
08:00:00 20 0
08:02:00 30 0
20:51:00 10 0
08:10:00 5 0
08:12:00 10 1
20:50:00 10 0
08:01:30 15 1
20:53:00 10 1
3 0
答案为：
08:00:00 08:00:00 0
08:01:30 08:01:30 0
08:02:00 08:02:00 0
08:10:00 08:16:30 7
08:12:00 08:20:00 8
20:50:00 20:50:00 0
20:51:00 20:51:00 0
20:52:00 20:52:00 0
3 3 2

//正常的测试例子，有vip和viptable
9
20:52:00 10 0
07:59:59 20 0
08:02:00 30 0
20:51:00 10 0
08:10:00 5 0
08:12:00 10 1
20:50:00 10 0
08:01:30 15 1
20:53:00 10 1
3 1
2
答案为：
07:59:59 08:00:00 0
08:01:30 08:01:30 0
08:02:00 08:02:00 0
08:12:00 08:16:30 5
08:10:00 08:20:00 10
20:50:00 20:50:00 0
20:51:00 20:51:00 0
20:52:00 20:52:00 0
3 3 2



//边缘测试例子
1
21:00:00 10 1
3 3
1 2 3

1
20:59:59 10 1
3 3
1 2 3

0
3 1
2

//vip桌子分配例子，有vip桌子时，优先把vip分到编号小的vip桌子，而不是编号小的vip桌子
4
06:00:00 30 1
08:00:00 30 1
10:00:00 30 1
12:00:00 30 1
5 1
3
答案为：
06:00:00 08:00:00 120
08:00:00 08:00:00 0
10:00:00 10:00:00 0
12:00:00 12:00:00 0
1 0 3 0 0

//超过两小时的例子
2
18:00:00 180 1
20:00:00 60 1
1 1
1
答案为：
18:00:00 18:00:00 0
20:00:00 20:00:00 0
2

//关于四舍五入为1分钟的例子，大约等于30秒才+1分钟，小于30则不+
3
07:59:31 60 1
07:59:29 60 1
08:00:30 100 1
2 1
1
答案为：
1
07:59:29 08:00:00 1
07:59:31 08:00:00 0
08:00:30 09:00:00 60
2 1
*/
string int2str(int a)
{
	char n = a / 10 + '0';
	char m = a % 10 + '0';
	string tmp = "";
	tmp += n;
	tmp += m;
	return tmp;

}
int char2int(char a)
{
	int tmp = a - '0';
	return tmp;
}
int time2int(string a)
{
	int hour = char2int(a[0]) * 10 + char2int(a[1]) - 8;
	int min = char2int(a[3]) * 10 + char2int(a[4]);
	int sec = char2int(a[6]) * 10 + char2int(a[7]);
	return hour * 3600 + min * 60 + sec;
}
struct playerNode{
	string arrive;
	int playTime, waitTime, serve;
	bool isVip;
	string serveStr();
	int waitInt();
	int serveTableNum;
	playerNode() :arrive(""), serve(maxServe), playTime(0), waitTime(0), isVip(false){};
	playerNode(string a, int p, bool v) :arrive(a), serve(maxServe), playTime(p), waitTime(0), isVip(v){};
};
string playerNode::serveStr()
{
	int hour = serve / 3600;
	int min = (serve - hour * 3600) / 60;
	int sec = serve % 60;
	return int2str(hour + 8) + ":" + int2str(min) + ":" + int2str(sec);
}
int playerNode::waitInt()
{
	int diff = serve - time2int(arrive);
	int min = diff / 60;
	if (diff % 60 >= 30)
		min++;
	return min;
}
struct tableNode{
	bool isVip;
	int playIndex;//当前玩家index
	int serveNum;//已经服务的玩家数量

	tableNode() :isVip(false), playIndex(-1), serveNum(0) {};
};
bool cmp(const playerNode&a, const playerNode&b)
{
	return a.arrive < b.arrive;
}
bool cmp2(const playerNode&a, const playerNode&b)
{//按照服务时间排序
	return a.serve < b.serve;
}
int main(void)
{
	int playerNum;
	cin >> playerNum;
	vector<playerNode> player(playerNum);
	vector<int> vipPlayer(0);
	for (int i = 0; i < playerNum; i++)
	{//输入玩家信息
		string arrive;
		int playTime;
		bool isVip;
		cin >> arrive >> playTime >> isVip;
		if (playTime > 120)
			playTime = 120;
		playTime *= 60;
		player[i].arrive = arrive;
		player[i].playTime = playTime;
		player[i].isVip = isVip;
	}
	sort(player.begin(), player.end(), cmp);

	for (int i = 0; i < playerNum; i++)
	{//建立vip队列
		if (player[i].isVip) vipPlayer.push_back(i);
	}

	int tableNum;
	int vipTableNum;
	cin >> tableNum >> vipTableNum;
	vector<tableNode> table(tableNum);
	vector<int> vipTable(0);
	int vipIndex = 0;
	int playerIndex = 0;
	for (int i = 0; i < vipTableNum; i++)
	{//输入vip桌子
		int a;
		cin >> a;
		table[a - 1].isVip = true;
		vipTable.push_back(a - 1);
	}

	for (int now = 0; now < 13 * 3600; now++)
	{
		for (int i = 0; i < table.size(); i++)
		{//遍历所有桌子，处理正在玩的玩家
			if (table[i].playIndex != -1)
			{//桌子有人
				player[table[i].playIndex].playTime--;
				if (player[table[i].playIndex].playTime <= 0)
				{//清空桌子
					table[i].playIndex = -1;
				}
			}
		}
		if (vipIndex < vipPlayer.size())
		{//先服务vip玩家
			for (int j = 0; j < vipTable.size(); j++)
			{
				while (vipIndex < vipPlayer.size() && player[vipPlayer[vipIndex]].serve != maxServe)
				{//跳过已经被服务的vip玩家，主要卡在这里
					vipIndex++;
				}
				int i = vipTable[j];//用i表示vip桌子
				if (table[i].playIndex == -1 && vipIndex < vipPlayer.size() && time2int(player[vipPlayer[vipIndex]].arrive) <= now)
				{
					table[i].serveNum++;
					table[i].playIndex = vipPlayer[vipIndex];
					player[vipPlayer[vipIndex]].serveTableNum = i;
					player[vipPlayer[vipIndex]].serve = now;
					vipIndex++;

				}
			}
		}

		if (playerIndex < player.size())
		{//服务剩下的玩家,普通玩家和vip玩家混在一起
			for (int i = 0; i < table.size(); i++)
			{
				while (playerIndex < player.size() && player[playerIndex].serve != maxServe)
				{//确保当前playerIndex的玩家是没有被服务的
					playerIndex++;
				}
				if (table[i].playIndex == -1 && playerIndex < player.size() && time2int(player[playerIndex].arrive) <= now)
				{
					table[i].serveNum++;
					table[i].playIndex = playerIndex;
					player[playerIndex].serveTableNum = i;
					player[playerIndex].serve = now;
					playerIndex++;
				}
			}
		}
	}

	sort(player.begin(), player.end(), cmp2);
	for (int i = 0; i < player.size(); i++)
	{
		if (player[i].serve != maxServe)
		{
			cout << player[i].arrive << " " << player[i].serveStr() << " " << player[i].waitInt() /*<<  " " << player[i].serveTableNum*/ << endl;
		}
	}
	for (int i = 0; i < table.size(); i++)
	{
		cout << table[i].serveNum;
		if (i != table.size() - 1)
			cout << " ";
	}


	return 0;
}