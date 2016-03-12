class Solution {
public:
	vector<int> grayCode(int n) {
		vector<int> gray;

		gray.push_back(0);
		if (n == 0) return gray;
		gray.push_back(1);

		for (int digit = 1; digit<n; digit++)
		{
			int size = gray.size();
			for (int i = size - 1; i >= 0; --i)
			{
				gray.push_back((1 << digit) + gray[i]);
			}
		}
		return gray;
	}
};