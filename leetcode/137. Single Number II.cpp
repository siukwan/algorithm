class Solution {
public:
	int singleNumber(vector<int>& nums) {
		vector<int> digit(32, 0);

		for (int i = 0; i<nums.size(); ++i)
		{
			for (int j = 0; j<32; ++j)
			{
				if ((1 << j)&nums[i])
					digit[j] = (digit[j] + 1) % 3;
			}
		}
		int ret = 0;
		for (int i = 0; i<32; ++i)
		{
			if (digit[i])
				ret += (digit[i] << i);
		}
		return ret;
	}
};