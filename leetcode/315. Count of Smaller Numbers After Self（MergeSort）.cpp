class Solution {
public:
	vector<int> countSmaller(vector<int>& nums) {
		vector<node> num(nums.size());
		for (int i = 0; i<nums.size(); ++i)
		{
			num[i].idx = i;
			num[i].cnt = 0;
			num[i].val = nums[i];
		}
		vector<node> tmpNums(nums.size());

		Msort(num, tmpNums, 0, num.size() - 1);

		vector<int> result(nums.size());
		for (int i = 0; i<num.size(); ++i)
		{
			result[num[i].idx] = num[i].cnt;
		}

		return result;
	}
	struct node{
		int val;//值
		int cnt;//右边比它大的数
		int idx;//原来的idx
		node() :val(0), cnt(0), idx(0){};
	};
	void Merge(vector<node>&nums, vector<node>&tmpNums, int l, int k, int r)
	{
		int i = l, j = k + 1;
		int idx = l;
		while (i <= k&j <= r)
		{
			if (nums[i].val <= nums[j].val)
			{//填充左边的数，证明之前填充的右边的数比这个数小，我们需要查询之前右边填充了多少个数字
				nums[i].cnt += j - (k + 1);
				tmpNums[idx++] = nums[i++];
			}
			else
				tmpNums[idx++] = nums[j++];
		}
		while (i <= k)
		{
			nums[i].cnt += j - (k + 1);
			tmpNums[idx++] = nums[i++];
		}
		while (j <= r)
			tmpNums[idx++] = nums[j++];

		for (i = l; i <= r; ++i)
		{
			nums[i] = tmpNums[i];
		}
	}

	void Msort(vector<node>&nums, vector<node>&tmpNums, int l, int r)
	{
		if (l >= r) return;

		int k = (l + r) / 2;
		Msort(nums, tmpNums, l, k);
		Msort(nums, tmpNums, k + 1, r);
		Merge(nums, tmpNums, l, k, r);
	}
};