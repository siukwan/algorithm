class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		int zeroIdx = 0;
		for (int i = 0; i<nums.size(); ++i)
		{
			if (nums[i] != 0)
				nums[zeroIdx++] = nums[i];
		}
		for (; zeroIdx<nums.size(); ++zeroIdx)
		{
			nums[zeroIdx] = 0;
		}
	}
};