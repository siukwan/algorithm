/*
题目描述

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。
*/
class Solution {
public:
	int InversePairs(vector<int> data) {
		vector<int> tmp(data.size());
		return MSort(data, tmp, 0, data.size() - 1);
	}

	int MSort(vector<int>&a, vector<int>&tmp, int l, int r)
	{
		if (l >= r) return 0;
		int k = (l + r) / 2;
		int left = MSort(a, tmp, l, k);
		int right = MSort(a, tmp, k + 1, r);
		int count = Merge(a, tmp, l, k, r);
		return left + right + count;
	}
	int Merge(vector<int>&a, vector<int>&tmp, int l, int k, int r)
	{
		int i = k;
		int j = r;
		int p = r;
		int count = 0;
		while (i >= l&&j >= k + 1)
		{
			if (a[i]>a[j])
			{
				tmp[p--] = a[i--];
				count += j - k;
			}
			else
				tmp[p--] = a[j--];
		}

		while (i >= l)
			tmp[p--] = a[i--];
		while (j >= k + 1)
			tmp[p--] = a[j--];

		for (i = l; i <= r; ++i)
			a[i] = tmp[i];
		return count;
	}
};