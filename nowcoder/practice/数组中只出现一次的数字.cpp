/*
题目描述

一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
*/
class Solution {
public:
	void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
		if (data.size() <= 1)
		{
			*num1 = 0;
			*num2 = 0;
			return;
		}
		int tmp = 0;
		//对所有数进行异或，得到的结果相当于num1和num2的异或
		for (int i = 0; i<data.size(); ++i)
		{
			tmp ^= data[i];
		}

		//找出两个数的第一个不同的位，后面会根据这个不同位，把数组分成两部分
		int dif = 1;
		for (; (dif&tmp) == 0; dif = dif << 1)
		{
		}
		tmp = 0;
		for (int i = 0; i<data.size(); ++i)
		{
			if ((dif&data[i])>0)
				tmp ^= data[i];
		}
		*num1 = tmp;
		tmp = 0;
		for (int i = 0; i<data.size(); ++i)
		{
			if ((dif&data[i]) == 0)
				tmp ^= data[i];
		}
		*num2 = tmp;
	}
};