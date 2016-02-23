/*
题目描述

求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

*/
class Solution {
public:
	int Sum_Solution(int n) {
		int sum = n;
		//当sum为0时，不会执行后半个处理
		sum && (sum += Sum_Solution(n - 1));
		return sum;
	}
};