/*
题目描述

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。

*/
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.size() == 0) return false;
		return check(sequence, 0, sequence.size() - 1);
	}

	//把数组划分为两部分，递归检测
	bool check(vector<int>& sequence, int l, int r)
	{
		if (l >= r) return true;
		int i;
		for (i = l; i<r; i++)
		{
			if (sequence[i]>sequence[r])
				break;
		}


		for (int j = i; j<r; j++)
		{
			//如果后半部分存在比末尾小的数，则false
			if (sequence[j]<sequence[r])
				return false;
		}

		return check(sequence, l, i - 1) && check(sequence, i, r - 1);
	}
};