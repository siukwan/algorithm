/*
题目：
1.首先对数组进行BST排序，去掉重复的情况。
2.排序的同时对每个元素的出现次数进行统计。
3.记录排序后，元素所在的位置。
4.使用树状数组记录排序后数组的统计情况。
5.进行查询时，先把当前元素的出现次数，在树状数组里-1，然后查询该元素前面元素的出现次数总和。
*/


#include<string>
#include <iomanip>
#include<fstream>
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
//#include<stack>
#include<vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<int> tree;
	//树状数组函数：
	int lowbit(int x)
	{
		return (x&-x);
	}

	void add(int x, int val)
	{
		for (int i = x; i<tree.size(); i += lowbit(i))
			tree[i] += val;
	}

	int get(int x)
	{
		int sum = 0;
		for (int i = x; i; i -= lowbit(i))
			sum += tree[i];
		return sum;
	}

	vector<int> countSmaller(vector<int>& nums) {

		set<int> sortNumsSet;
		map<int, int> times;

		//对nums进行排序和统计
		for (int i = 0; i<nums.size(); i++)
		{
			times[nums[i]]++;
			sortNumsSet.insert(nums[i]);
		}
		//建立树状数组
		tree = vector<int>(sortNumsSet.size() + 1, 0);

		map<int, int> pos;
		vector<int> sortNums(sortNumsSet.size(), 0);
		set<int>::iterator ite = sortNumsSet.begin();
		//复制到新的数组中，并且记录元素的位置。
		for (int i = 0; i<sortNums.size(); i++)
		{
			sortNums[i] = *ite;
			pos[sortNums[i]] = i + 1;
			ite++;
			add(i + 1, times[sortNums[i]]);
		}

		vector<int> ans(nums.size(), 0);
		for (int i = 0; i<nums.size(); i++)
		{
			//当前元素的出现次数－1
			add(pos[nums[i]], -1);
			//获取nums[i]前面的元素总数
			ans[i] = get(pos[nums[i]] - 1);
			//cout<<ans[i]<<' ';
		}

		return ans;

	}
};
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	vector<int> nums = { 7, 2, 7, 2, 0 };
	Solution sols;
	nums = sols.countSmaller(nums);
	for (int i = 0; i < nums.size(); i++)
		printf("%d ", nums[i]);
	return  0;
}
