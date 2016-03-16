class Solution {
public:
	vector<int> getRow(int rowIndex) {
		vector<int>result(rowIndex + 1, 1);

		for (int i = 1; i <= (rowIndex + 1) / 2; ++i)
		{
			unsigned long long tmp = result[i - 1];
			if (tmp%i == 0)
			{
				tmp /= i;
				tmp *= (rowIndex + 1 - i);
			}
			else
			{
				tmp *= (rowIndex + 1 - i);
				tmp /= i;
			}
			result[i] = tmp;
			result[rowIndex - i] = result[i];
		}
		return result;
	}
};