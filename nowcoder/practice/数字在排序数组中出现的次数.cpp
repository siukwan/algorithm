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


//解法二，使用二分法找出首位和末位
class Solution {
public:
	int GetNumberOfK(vector<int> data, int k) {

		int l = getFirstK(data, k);
		if (l == -1) return 0;
		int r = getLastK(data, k);
		return r - l + 1;

	}

	int getFirstK(vector<int>&data, int k)
	{
		int l = 0;
		int r = data.size() - 1;
		int mid = (l + r) / 2;

		while (l <= r)
		{
			mid = (l + r) / 2;
			if (data[mid] == k)
			{
				if (mid>0 && data[mid - 1] != k)
					return mid;
				else if (mid == 0)
					return mid;
				else
					r = mid - 1;
			}
			else if (data[mid]<k)
				l = mid + 1;
			else
				r = mid - 1;
		}

		return -1;
	}

	int getLastK(vector<int>&data, int k)
	{
		int l = 0;
		int r = data.size() - 1;
		int mid = (l + r) / 2;

		while (l <= r)
		{
			mid = (l + r) / 2;
			if (data[mid] == k)
			{
				if (mid<data.size() - 1 && data[mid + 1] != k)
					return mid;
				else if (mid == data.size() - 1)
					return mid;
				else
					l = mid + 1;
			}
			else if (data[mid]<k)
				l = mid + 1;
			else
				r = mid - 1;
		}

		return -1;
	}
};