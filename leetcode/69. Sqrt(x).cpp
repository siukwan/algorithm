class Solution {
public:
	int mySqrt(int x) {
		int c = 1;
		int ans = 0;
		while (1)
		{
			int tmp = ans + c;
			unsigned long long tmp2 = tmp*tmp;
			if (tmp2 <= x)
			{
				ans += c;
				c = (c << 1);
			}
			else
			{
				if (c == 1) return ans;
				c = 1;
			}
		}
	}
};