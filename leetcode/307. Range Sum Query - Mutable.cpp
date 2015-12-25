/*
题目：
区间求和和更新问题，使用树状数组解决
需要注意的是：
1.树状数组的下标需要从1开始，不然在使用(x&-x)时恒为0
2.更新完树状数组后，原数组也要进行更新（卡在这里）
*/


//#include<string>
//#include <iomanip>
#include<fstream>
//#include<set>
//#include<queue>
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

class NumArray {
public:
	vector<int> num;
	vector<int> tree;

	NumArray(vector<int> &nums) {
	    //初始化两个数组，一个是num，用来存储原来的数组
		num = nums;
		//一个是树状数组，存储和信息
		tree = vector<int>(nums.size() + 1, 0);
		for (int i = 0; i < nums.size(); i++)
		{//采用add操作进行更新
			add(i + 1, nums[i]);
		}
	}

	void update(int i, int val) {
	    //求出差值，进行add
		int diff = val - num[i];
		add(i + 1, diff);
		//由于update操作设计到val-num[i]，所以除了更新树状数组，原数组也需要更新
		num[i] = val;
	}

	int sumRange(int i, int j) {
	    //求出1到j+1的和，求出1到i的和，然后进行相减
		return get(j+1) - get(i);
	}
	//x=0时返回0，所以x必须>=1
	int lowbit(int x)
	{
		return (x&-x);
	}
	void add(int x, int value)
	{
		for (int i = x; i < tree.size(); i += lowbit(i))
			tree[i] += value;
	}
	
	//get操作是得到1到x的和
	int get(int x)
	{
		int sum = 0;
		for (int i = x; i; i -= lowbit(i))
			sum += tree[i];
		return sum;
	}
};

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);

/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	vector<int> nums = { 7, 2, 7, 2, 0 };
	NumArray numArray(nums);
	numArray.update(4, 6);
	numArray.update(0, 2);
	numArray.update(0, 9);
	cout << numArray.sumRange(4, 4)<<endl;
	numArray.update(3, 8);
	cout << numArray.sumRange(0, 4)<<endl;
	numArray.update(4, 1);
	cout << numArray.sumRange(0, 3)<<endl;
	cout << numArray.sumRange(0, 4)<<endl;
	numArray.update(0, 4);
	return  0;
}
