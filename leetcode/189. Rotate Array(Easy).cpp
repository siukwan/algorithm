
class Solution {
public:
	void rotate(vector<int>& nums, int k) {
		int n = nums.size();
		k = k%n;

		// Reverse the first n - k numbers.
		// Index i (0 <= i < n - k) becomes n - k - i.
		reverse(nums, 0, n - k - 1);

		// Reverse tha last k numbers.
		// Index n - k + i (0 <= i < k) becomes n - i.
		reverse(nums, n - k, n - 1);

		// Reverse all the numbers.
		// Index i (0 <= i < n - k) becomes n - (n - k - i) = i + k.
		// Index n - k + i (0 <= i < k) becomes n - (n - i) = i.
		reverse(nums, 0, n - 1);
	}
	void reverse(vector<int>&nums, int start, int end)
	{
		for (int i = start; i <= (start + end) / 2; i++)
		{
			swap(nums[i], nums[end - i + start]);
		}
	}
};