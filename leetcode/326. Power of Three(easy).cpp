/*
326. Power of Three(easy)

Given an integer, write a function to determine if it is a power of three.
Follow up:
Could you do it without using any loop / recursion?
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	bool isPowerOfThree(int n) {
		/*
		if (n < 3)
		{
			if (n == 1) return true;
			else return false;
		}
		else
		{
			if (n % 3 == 0)
				return isPowerOfThree(n / 3);
			else return false;
		}
		*/
		return n>0 ? !(1162261467 % n) : 0;
	}
};
int main()
{
	Solution sols;
	cout << sols.isPowerOfThree(9) << endl;
	return 0;
}
