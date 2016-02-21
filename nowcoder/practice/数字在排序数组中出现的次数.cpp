/*
题目描述

统计一个数字在排序数组中出现的次数。
*/
class Solution {
public:
	int GetNumberOfK(vector<int> data, int k) {
		if (data.size() == 0) return 0;
		int l = 0;
		int r = data.size() - 1;
		int mid = (l + r) / 2;

		while (l<r)
		{
			mid = (l + r) / 2;
			if (data[mid] == k)
				break;
			else if (data[mid]<k)
				l = mid + 1;
			else
				r = mid - 1;
		}

		if (data[mid] == k)
		{
			int count = 0;
			for (int i = mid; i >= 0; --i)
			{
				if (data[i] == k)
					count++;
				else break;
			}
			for (int i = mid + 1; i<data.size(); ++i)
			{
				if (data[i] == k)
					count++;
				else break;
			}
			return count;

		}
		else
			return 0;
	}

};