class Solution {
public:
	int addDigits(int num) {
		int result = num;
		while (num / 10 >= 1)
		{
			result = 0;
			while (num != 0)
			{
				result += num % 10;
				num /= 10;
			}
			num = result;
		}
		return result;

	}
};