class Solution {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.size() <= 1) return 0;

		int low = prices[0], high = 0;
		int profit = 0;
		int res = 0;
		for (int i = 1; i < prices.size(); ++i)
		{
			//发现利润下降时，及时卖出
			if (prices[i] - low < profit)
			{
				res += profit;
				profit = 0;
				low = prices[i];
			}
			//如果买入价格更低，晚点再买
			if (prices[i] < low)
				low = prices[i];
			else if (prices[i] - low >= profit)
				profit = prices[i] - low;//如果今天买的利润比前些天大，可以考虑今天卖出
		}
		res += profit;
		return res;
	}
};