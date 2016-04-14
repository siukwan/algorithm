/*
有一些数的素因子只有3、5、7，请设计一个算法，找出其中的第k个数。
给定一个数int k，请返回第k个数。保证k小于等于100。
测试样例：
3
返回：7

*/
class KthNumber {
public:
	int findKth(int k) {
		// write code here
		int idx[3] = { 1, 1, 1 };//三个指针
		vector<int> result = { 0, 3, 5, 7 };
		for (int i = 3; i <= k; ++i)
		{
			int a = result[idx[0]] * 3;
			int b = result[idx[1]] * 5;
			int c = result[idx[2]] * 7;

			int tmp = min(min(a, b), c);
			result.push_back(tmp);

			//避免出现3*5和5*3的情况
			if (tmp == a) idx[0]++;
			if (tmp == b) idx[1]++;
			if (tmp == c) idx[2]++;
		}
		return result[k];
	}
};