/*
小v今年有n门课，每门都有考试，为了拿到奖学金，小v必须让自己的平均成绩至少为avg。每门课由平时成绩和考试成绩组成，满分为r。现在他知道每门课的平时成绩为ai ,若想让这门课的考试成绩多拿一分的话，小v要花bi 的时间复习，不复习的话当然就是0分。同时我们显然可以发现复习得再多也不会拿到超过满分的分数。为了拿到奖学金，小v至少要花多少时间复习。

输入描述:
第一行三个整数n,r,avg(n大于等于1小于等于1e5，r大于等于1小于等于1e9,avg大于等于1小于等于1e6)，接下来n行，每行两个整数ai和bi，均小于等于1e6大于等于1


输出描述:
一行输出答案。

输入例子:
5 10 9
0 5
9 1
8 1
0 1
9 100

输出例子:
43
*/
//注意平均分本来就大于需求的情况，这是需要付出的时间为0
#include<string>
#include <iomanip>
#include<vector>
#include <algorithm>
#include<stack>
#include<set>
#include<queue>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include <sstream>
#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
using namespace std;
struct course{

	unsigned long long now;
	unsigned long long left;
	unsigned long long time;
	course() :now(0), left(0), time(0){};
};
bool cmp(const course&a, const course&b)
{
	return a.time < b.time;
}
int main()
{
	unsigned long long n, r, avg;
	while (scanf("%llu", &n) != EOF)
	{
		scanf("%llu%llu", &r, &avg);
		vector<course> c(n);
		unsigned long long nowScore = 0;//现在的分数
		for (int i = 0; i < n; ++i)
		{
			scanf("%llu%llu", &c[i].now, &c[i].time);
			c[i].left = r - c[i].now;
			nowScore += c[i].now;
		}
		//按照时间排序
		sort(c.begin(), c.end(), cmp);

		unsigned long long total = n*avg;
		unsigned long long totalTime = 0;
		for (int i = 0; i < c.size(); ++i)
		{
			if (nowScore + c[i].left <= total)//这门课的分数全拿了还达不到要求
			{
				nowScore += c[i].left;
				totalTime += c[i].left*c[i].time;
			}
			else//超出了分数
			{
				if (nowScore >= total) break;//如果已经大于平均分，则直接break
				long long tmp = total - nowScore;
				nowScore = total;
				totalTime += tmp*c[i].time;
				break;
			}

		}
		printf("%llu\n", totalTime);
	}
	return 0;
}