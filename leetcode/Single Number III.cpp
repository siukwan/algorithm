class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int ret = 0;
		for (int i = 0; i<nums.size(); i++)
		{
			ret ^= nums[i];
		}

		int digitIndex = 0;
		for (int i = 0; i<32; i++)
		{
			if (((ret >> i) & 1) == 1)
				digitIndex = i;
		}
		int x = 0, y = 0;
		for (int i = 0; i<nums.size(); i++)
		{
			if (((nums[i] >> digitIndex) & 1) == 1)
				x ^= nums[i];
			else
				y ^= nums[i];
		}
		vector<int> result(0);
		result.push_back(x);
		result.push_back(y);
		return result;
	}
};