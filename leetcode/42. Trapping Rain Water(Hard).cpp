/*
思路：

1.使用两个指针，从两端往内遍历。

2.如果左边的高度小于右边的高度，那么左边的高度则可以填充雨水，但是填充为多少呢？这个时候，需要看左边的左边的最大高度maxL（简称为左边的最大高度），我们可以把雨水填充为左边的最大高度maxL。为什么能够填充为左边的最大高度maxL？

因为在遍历过程中，我们需要左边的高度小于右边的高度才会进行更新最大高度的操作，在这个过程中，我们可以保证存在一个height[right]在maxL的右边，且height[right]>maxL，因此，我们可以填充为左边的最大高度maxL。

3.右边同理。

4.时间复杂度为O(n)，空间复杂度为O(1)。

*/

class Solution {
public:
	int trap(vector<int>& height) {
		int left = 0; int right = height.size() - 1;
		int maxL = 0, maxR = 0;
		int result = 0;
		while (left<right)
		{
			if (height[left]<height[right])             {
				if (height[left]>maxL)
					maxL = height[left];//遇到新的高度，则无法填充雨水
				else//height[left]<=maxL                     
					result+=maxL-height[left];                 
				left++;             
			}            
			else             
			{                 
				if(height[right]>maxR)
					maxR = height[right];//遇到新的高度，无法填充雨水
			else
				result += maxR - height[right];
				right--;
			}
		}

		return result;
	}
};