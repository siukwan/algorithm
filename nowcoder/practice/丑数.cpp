/*
题目描述

把只包含因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
*/
class Solution {
public:
	int GetUglyNumber_Solution(int index) {
		vector<int> ugly(1, 1);//初始化1
		int ptr2 = 0, ptr3 = 0, ptr5 = 0;
		int ugly2, ugly3, ugly5;
		int minUgly;
		while (ugly.size()<index)
		{
			ugly2 = ugly[ptr2] * 2;
			ugly3 = ugly[ptr3] * 3;
			ugly5 = ugly[ptr5] * 5;
			minUgly = min(min(ugly2, ugly3), ugly5);
			ugly.push_back(minUgly);

			//会出现重复，譬如2*3和3*2都为6，需要同时跳过
			if (minUgly == ugly2)
				ptr2++;
			if (minUgly == ugly3)
				ptr3++;
			if (minUgly == ugly5)
				ptr5++;
		}
		return ugly[index - 1];
	}
};