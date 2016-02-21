/*
题目描述

输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。
输出描述:
对应每个测试案例，输出两个数，小的先输出。
*/

class Solution {
public:
	vector<int> FindNumbersWithSum(vector<int> array, int sum) {
		map<int, bool>m;
		vector<pair<int, int>> tmp(0);

		for (int i = 0; i<array.size(); ++i)
		{
			int target = sum - array[i];
			if (m.find(target) == m.end())
				m[array[i]] = true;
			else
			{
				tmp.push_back({ min(target, array[i]), max(target, array[i]) });
			}
		}
		vector<int> result(0);
		if (tmp.size() == 0) return result;
		if (tmp.size() == 1)
		{
			result.push_back(tmp[0].first);
			result.push_back(tmp[0].second);
			return result;
		}
		else
		{
			int a = tmp[0].first;
			int b = tmp[0].second;
			for (int i = 1; i<tmp.size(); ++i)
			{
				if (tmp[i].first*tmp[i].second<a*b)
				{
					a = tmp[i].first;
					b = tmp[i].second;
				}
			}
			result.push_back(a);
			result.push_back(b);
			return result;
		}
	}
};