/*
题目描述

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个非递减序列的一个旋转，输出旋转数组的最小元素。例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
*/
class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		//需要进行判断，不判断会发生段错误
		if (rotateArray.size() == 0)
			return 0;
		int low = 0;
		int mid = low;
		int high = rotateArray.size() - 1;

		while (rotateArray[low] >= rotateArray[high])
		{
			if (high - low == 1)
			{
				mid = high;
				break;
			}
			mid = (low + high) / 2;
			if (rotateArray[mid] == rotateArray[low] && rotateArray[high] == rotateArray[low])
			{
				int result = rotateArray[low];
				for (int i = low; i <= high; i++)
				{
					if (rotateArray[i]<result)
						result = rotateArray[i];
				}
				return result;
			}
			if (rotateArray[mid] <= rotateArray[high])
				high = mid;
			else if (rotateArray[mid] >= rotateArray[low])
				low = mid;

		}
		return rotateArray[mid];
	}
};