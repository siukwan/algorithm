class Solution {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> result;

		for (int i = 0; i<numRows; ++i)
		{
			vector<int> row(i + 1, 1);
			for (int j = 0; j <= i / 2 && i != 0; ++j)
			{
				if (j != 0)
				{
					row[j] = result.back()[j - 1] + result.back()[j];
					row[row.size() - 1 - j] = row[j];
				}

			}
			result.push_back(row);
		}
		return result;
	}
};