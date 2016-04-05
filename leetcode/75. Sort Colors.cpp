class Solution {
public:
	void sortColors(vector<int>& nums) {
		int red = 0, blue = nums.size() - 1, white = 0;
		int other = nums.size() - 1;
		while (red <= other)
		{
			while (red <= other&&nums[red] == 0)
				red++;
			while (red <= other&&nums[other] != 0)
				other--;
			if (red <= other)
				swap(nums[red], nums[other]);
		}
		white = red;
		while (white <= blue)
		{
			while (white <= blue&&nums[white] == 1)
				white++;
			while (white <= blue&&nums[blue] == 2)
				blue--;
			if (white <= blue)
				swap(nums[white], nums[blue]);
		}

	}
};