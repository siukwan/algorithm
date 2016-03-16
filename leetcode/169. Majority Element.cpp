class Solution {
public:
	int majorityElement(vector<int>& nums) {
		if (nums.size() == 0) return 0;
		int res = nums[0];
		int count = 1;
		for (int i = 1; i<nums.size(); ++i)
		{
			if (res != nums[i])
			{
				count--;
				if (count == 0)
				{
					count = 1;
					res = nums[++i];
				}
			}
			else
				count++;
		}
		return res;
	}
};