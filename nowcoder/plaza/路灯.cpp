/*
一条长l的笔直的街道上有n个路灯，若这条街的起点为0，终点为l，第i个路灯坐标为ai，每盏灯可以覆盖到的最远距离为d，为了照明需求，所有灯的灯光必须覆盖整条街，但是为了省电，要是这个d最小，请找到这个最小的d。
*/

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

int main()
{
	unsigned long long n;
	while (scanf("%llu", &n) != EOF)
	{
		bool start = false, end = false;
		set<unsigned long long> lightSet;
		unsigned long long final;
		scanf("%llu", &final);
		for (int i = 0; i < n; ++i)
		{
			unsigned long long tmp;
			scanf("%llu", &tmp);
			lightSet.insert(tmp);
			if (!start&&tmp == 0) start = true;
			if (!end&&tmp == final) end = true;
		}
		vector<unsigned long long> light(lightSet.begin(), lightSet.end());

		unsigned long long dis = 0;

		for (int i = 1; i < light.size(); ++i)
		{
			dis = max(dis, light[i] - light[i - 1]);
		}
		double result = dis;
		result /= 2;
		if (!start)//起点没灯
			result = max(result, (double)(final - light.back()));
		if (!end)//终点没灯
			result = max(result, (double)light[0]);
		printf("%.2lf\n", result);

	}
	return 0;
}