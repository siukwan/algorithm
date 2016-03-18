class Solution {
public:
	vector<int> countBits(int num) {
		int idx = 0, n2 = 1;
		vector<int> result;
		result.push_back(0);
		for (int i = 1; i <= num; ++i)
		{
			if (i == n2)
			{
				idx = 0;
				n2 *= 2;
			}
			result.push_back(result[idx++] + 1);
		}
		return result;
	}
};