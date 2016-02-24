/*
题目描述

给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。不能使用除法。

*/
class Solution {
public:
	vector<int> multiply(const vector<int>& A) {
		vector<int> result(0);
		if (A.size() == 0)
			return result;

		result = vector<int>(A.size(), 1);

		int tmp = 1;

		//前向乘积数组
		for (int i = 1; i<A.size(); ++i)
		{
			tmp *= A[i - 1];
			result[i] *= tmp;
		}

		tmp = 1;
		//后向乘积数组
		for (int i = A.size() - 2; i >= 0; --i)
		{
			tmp *= A[i + 1];
			result[i] *= tmp;
		}
		return result;
	}
};