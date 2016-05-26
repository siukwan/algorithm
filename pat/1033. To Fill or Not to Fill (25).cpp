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
/*
50 1300 12 8
6.00 1250
7.00 600
7.00 150
7.10 0
7.20 200
7.50 400
7.30 1000
6.85 300

50 1300 12 2
7.10 0
7.00 600

50 0 12 2
7.10 0
7.00 600

50 0 12 0

50 13000 12 2
7.10 0
7.00 600
*/
struct stationNode{
	double price;
	int position;
	stationNode() :price(0), position(0){};
};
struct gasNode{
	double price;//价格
	double cap;//容量
	double cost;//总价格
	double dist;
	gasNode() :price(0), cap(0), cost(0), dist(0){};
	gasNode(double p, double c) :price(p), cap(c), cost(0), dist(0){};
};
bool cmp(const stationNode&a, const stationNode&b)
{
	return a.position < b.position;
}
int main(void)
{
	int cMax, target, dAvg, n;
	cin >> cMax >> target >> dAvg >> n;
	n++;//把终点也作为一个站
	vector<stationNode> sta(n);
	for (int i = 0; i < n - 1; i++)
	{//初始化
		cin >> sta[i].price >> sta[i].position;
	}
	sta.back().position = target;//设置终点的距离
	sort(sta.begin(), sta.end(), cmp);//按照站的位置进行排序
	vector<gasNode> gas(0);//油箱数组
	int gasIndex = 0;//记录当前用到哪个油箱数组的油
	double totalGas = 0;
	if (0 >= sta[0].position)
	{//把第一个站加进去,包含价格信息和加了多少油
		gas.push_back(gasNode(sta[0].price, cMax));
		totalGas = cMax;
		//now += cMax*dAvg;
	}
	for (int now = 1; now < n; now++)
	{
		//needGas表示从i-1站到i站需要多少油
		double needGas = (sta[now].position - sta[now - 1].position) *1.0 / dAvg;

		//把油箱里的油减去需要用的油，计算得到油箱还剩多少油
		totalGas -= needGas;
		//在这里可以直接判断totalGas是否小于0，小于0表示油箱不够油跑下去，但是由于题目还需要求最长距离，所以这里不作处理，统计完邮箱所有的油再进行处理


		//遍历邮箱数组，利用gasIndex做开始位，减少时间复杂度
		for (int j = gasIndex; j < gas.size(); j++)
		{
			if (gas[j].cap > needGas)
			{//当前vector的油能够满足需求
				gas[j].cap -= needGas;//减去需要用的油，得到剩余的油
				gas[j].cost += needGas*gas[j].price;//计算这个vector的油已经耗费了多少钱
				gas[j].dist += needGas*dAvg;//计算这个vector的油走了多长的路
				gasIndex = j;//下次直接从这个vector计算油量
				needGas = 0;
				break;
			}
			else if (gas[j].cap < needGas)
			{//如果当前vector的油量不足
				gas[j].cost += gas[j].cap*gas[j].price;//计算这个vector的油耗费了多少钱
				gas[j].dist += gas[j].cap*dAvg;//计算这个vector的油走了多长的路
				needGas -= gas[j].cap;//除去这个vector的油，还需要多少油
				gasIndex = j;
			}
			else
			{//刚好等于需要的油，由于使用了double，基本不会出现这种needGas等于0的情况
				gas[j].cost += gas[j].cap*gas[j].price;//计算这个vector的油耗费了多少钱
				gas[j].dist += gas[j].cap*dAvg;//计算这个vector的油走了多长的路
				needGas -= gas[j].cap;//needGas为0
				gasIndex = j + 1;//直接指向下个vector
				break;
			}
		}

		if (needGas > 0)
		{//当前油箱的总油量不能走到当前地点
			double totalDist = 0;
			//统计走了多少路
			for (int j = 0; j < gas.size(); j++)
				totalDist += gas[j].dist;

			printf("The maximum travel distance = %.2f", totalDist);
			return 0;
		}

		//能够到当前地点
		for (int j = gasIndex; j < gas.size(); j++)
		{//遍历邮箱里面存在的油，如果价格比当前油站要高，那么就更新价格
			//实际的意义相当于：到了当前的站还有油剩(这些油可加可不加)，且之前加的油价格比当前油站要高（这些油没必要在之前加），那么在之前就不加油了，全换成到这个站才加油
			if (gas[j].price>sta[now].price)
				gas[j].price = sta[now].price;
		}
		//把油补充满
		gas.push_back(gasNode(sta[now].price, cMax - totalGas));
		totalGas = cMax;
	}

	//计算总价格
	double totalCost = 0;
	for (int i = 0; i < gas.size(); i++)
	{
		totalCost += gas[i].cost;
	}
	printf("%.2lf", totalCost);
	return 0;
}