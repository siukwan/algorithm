/*
题目描述

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

*/
class Solution {
public:
	void Insert(int num)
	{
		if (minSize == maxSize)
		{
			if (minSize == 0)
				pushMin(num);
			else
			{//
				if (num<maxHeap[0])
				{
					int x = popMax();
					pushMin(x);
					pushMax(num);
				}
				else
					pushMin(num);
			}
		}
		else
		{
			if (num>minHeap[0])
			{
				int x = popMin();
				pushMax(x);
				pushMin(num);
			}
			else
				pushMax(num);

		}
	}

	double GetMedian()
	{
		if (minSize == maxSize)
		{
			if (minSize == 0) return 0;
			else
			{
				double result = (minHeap[0] + maxHeap[0]) / 2.0;
				return result;
			}
		}
		else
			return minHeap[0];
	}
	Solution() :minSize(0), maxSize(0){}
	vector<int> minHeap;
	vector<int> maxHeap;
	int minSize, maxSize;
	void pushMin(int x)
	{
		if (minSize == 0)
		{
			minSize++;
			minHeap.push_back(x);
			return;
		}
		minHeap.push_back(x);
		int i = minSize++;
		int p = (i - 1) / 2;

		while (x<minHeap[p])
		{
			minHeap[i] = minHeap[p];
			if (i == 0) break;
			i = p;
			p = (i - 1) / 2;
		}

		minHeap[i] = x;
	}

	int popMin()
	{
		int result = minHeap[0];
		int x = minHeap[minSize - 1];
		minSize--;
		minHeap.pop_back();
		if (minSize == 0) return result;
		int i = 0;
		int a = i * 2 + 1;
		int b = a + 1;
		while (a<minSize)
		{
			if (b<minSize&&minHeap[a]>minHeap[b]) a = b;

			if (x>minHeap[a])
				minHeap[i] = minHeap[a];
			else break;

			i = a;
			a = i * 2 + 1;
			b = a + 1;
		}

		minHeap[i] = x;
		return result;

	}

	void pushMax(int x)
	{
		if (maxSize == 0)
		{
			maxSize++;
			maxHeap.push_back(x);
			return;
		}
		maxHeap.push_back(x);
		int i = maxSize++;
		int p = (i - 1) / 2;

		while (x>maxHeap[p])
		{
			maxHeap[i] = maxHeap[p];
			if (i == 0) break;
			i = p;
			p = (i - 1) / 2;
		}

		maxHeap[i] = x;
	}

	int popMax()
	{
		int result = maxHeap[0];
		int x = maxHeap[maxSize - 1];
		maxSize--;
		maxHeap.pop_back();
		if (maxSize == 0) return result;
		int i = 0;
		int a = i * 2 + 1;
		int b = a + 1;

		while (a<maxSize)
		{
			if (b<maxSize&&maxHeap[a]<maxHeap[b]) a = b;
			if (x<maxHeap[a])
				maxHeap[i] = maxHeap[a];
			else break;

			i = a;
			a = i * 2 + 1;
			b = a + 1;
		}
		maxHeap[i] = x;
		return result;
	}

};