/*
题目描述

给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。

主要需要考虑幂为0和为负数的情况
*/
class Solution {
public:
	double Power(double base, int exponent) {
		double result = 1;
		if (exponent == 0) return 1;
		else if (exponent<0)
		{
			base = 1 / base;
			exponent = -exponent;
		}
		for (int i = 0; i<exponent; i++)
			result *= base;
		return result;
	}
};


//方法二：
class Solution {
public:
	double Power(double base, int exponent) {

		if (exponent >= 0) return PowerPositive(base, exponent);
		else return PowerPositive(1 / base, -exponent);
	}

	double PowerPositive(double base, int exponent) {
		if (exponent == 0) return 1;
		if (exponent == 1) return base;

		double result = Power(base, exponent >> 1);
		result *= result;
		if (exponent & 0X1 == 1)
			result *= base;
		return result;
	}
};
