/*
题目描述

对于一个元素各不相同且按升序排列的有序序列，请编写一个算法，创建一棵高度最小的二叉查找树。
给定一个有序序列int[] vals,请返回创建的二叉查找树的高度。

*/
class MinimalBST {
public:
	int buildMinimalBST(vector<int> vals) {
		// write code here
		if (vals.size() == 0) return 0;
		int result = 1; int i = 0;
		for (i = 0; result<vals.size(); ++i)
			result *= 2;
		return i;
	}
};