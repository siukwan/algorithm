AC代码：
/*
1.在17:00:00前（包括17整）来的客户，都要确保一直执行完，即使超过了17点
2.只是对17:00:00后来的客户拒绝服务
3.逻辑顺序有问题，需要先插入，然后再减时间
*/
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
class customNode{
public:
	int process, start, arrivalSecond, waitTime;
	int calculateWaitTime();
	customNode() :process(-1), start(-1), arrivalSecond(-1), waitTime(-1){};
};
int time2int(string a)
{//string转化为00:00:00到现在的时间
	return ((a[0] - '0') * 10 + a[1] - '0') * 3600 + ((a[3] - '0') * 10 + a[4] - '0') * 60 + ((a[6] - '0') * 10 + a[7] - '0');
}
int customNode::calculateWaitTime()
{//计算等待时间
	return start - arrivalSecond;
}
bool cmp(const customNode&a, const customNode&b)
{
	return a.arrivalSecond < b.arrivalSecond;
}
int main(void)
{
	int n, k;
	cin >> n >> k;
	int startTime = 8 * 3600;//8点
	int endTime = 17 * 3600;//17点
	vector<customNode> custom(0);
	for (int i = 0; i < n; i++)
	{
		int hour, minute, second, process;
		scanf("%d:%d:%d %d", &hour, &minute, &second, &process);
		int arrivalTime = hour * 3600 + minute * 60 + second;
		if (arrivalTime <= endTime)
		{//小于17:00:00的才加入
			custom.push_back(customNode());
			custom.back().arrivalSecond = arrivalTime;
			custom.back().process = process * 60;
			custom.back().start = -1;
		}
	}
	sort(custom.begin(), custom.end(), cmp);
	n = custom.size();
	int query = 0;
	vector<int> window(k, -1);
	//while (query < n && query < k && custom[query].arrivalSecond <= startTime)
	//{//本来卡在了这里，插入时缺少判断时间是否合适
	//  window[query] = query;
	//  custom[query].start = startTime;//第一批到的人，记为0，即08:00:00开始处理
	//  query++;
	//}

	int now = startTime;
	for (int i = startTime; query < n; i++)
	{//注意结束条件是query>=n，即凡是压进队列的用户，都必须接受处理，17点后到来的用户已经不在队列中
		now = i;
		//先进行插入，遍历k个窗口
		for (int j = 0; j < k; j++)
		{

			if (window[j] == -1 && query < n)//窗口为空闲时
			{
				if (custom[query].arrivalSecond <= now)
				{//队列中还有客户，且客户的到达时间小于等于当前时间
					window[j] = query;
					custom[query].start = now;
					query++;
				}
			}
		}
		//进行减时间，如8点到的用户，现在刚好是8点，process为1分钟，那么process已经-1，为0了，所以即使空出来，也得等到8点01分才能插入（即等到下一个周期）
		for (int j = 0; j < k; j++)
		{//遍历k个窗口
			if (window[j] != -1)
			{
				int num = window[j];
				custom[num].process--;
				if (custom[num].process == 0)//当客户的处理时间为0时，代表结束
					window[j] = -1;//窗口置为空闲
			}
		}
	}

	int waitTime = 0;
	for (int i = 0; i < n; i++)
	{
		custom[i].waitTime = custom[i].calculateWaitTime();
		waitTime += custom[i].waitTime;
	}
	if (n == 0)
		printf("%.1f", 0.0);
	else
		printf("%.1f", waitTime / 60.0 / n);
	cout << endl;

	return 0;
}