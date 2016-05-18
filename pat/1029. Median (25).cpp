//#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
#include<set>
#include<queue>
#include<map>
//#include<unordered_set>
//#include<unordered_map>
//#include <sstream>
//#include "func.h"
//#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
using namespace std;
/*
0
0

1 100
0

0
1 100

1 10
1 100

1 10
2 20 30

2 10 20
2 30 40

3 10 20 30
3 40 50 60

4 10 20 30 70
4 40 50 60 80

3 10 20 30
4 40 50 60 80

2 3 4
0

*/

/*
{a[0],a[1],a[2],....a[i-1]  |   a[i],a[i+1],...a[m-1]}
{b[0],b[1],b[2],....b[j-1]  |   b[j],b[j+1],...b[n-1]}

*/
int findMedianSortedArrays(int *nums1, int*nums2, int m, int n) {

	if (m>n) return findMedianSortedArrays(nums2, nums1, n, m);
	int minIdx = 0, maxIdx = m;//第一个数组的范围
	int i, j;//两个数组的下标
	int num1, num2;
	int mid = (m + n + 1) >> 1;//为什么+1
	while (minIdx <= maxIdx)
	{
		i = (minIdx + maxIdx) >> 1;//取中间值
		j = mid - i;
		if (i<m && j>0 && nums2[j - 1] > nums1[i])
			minIdx = i + 1;
		else if (i>0 && j<n && nums2[j] < nums1[i - 1])
			maxIdx = i - 1;
		else
		{
			if (i == 0) num1 = nums2[j - 1];
			else if (j == 0) num1 = nums1[i - 1];
			else num1 = max(nums1[i - 1], nums2[j - 1]);
			break;
		}
	}
	return num1;
}

int main(void)
{
	int m, n;
	scanf("%d", &m);
	int *nums1 = new int[m];
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &nums1[i]);
	}
	scanf("%d", &n);
	int *nums2 = new int[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &nums2[i]);
	}
	//cout << findMedianSortedArrays(nums1, nums2, m, n) << endl;

	int *a, *b;

	if (m > n)
	{
		a = nums2;
		b = nums1;
		swap(m, n);
	}
	else
	{
		a = nums1;
		b = nums2;
	}
	/*
	{a[0],a[1],a[2],....a[i-1]  |   a[i],a[i+1],...a[m-1]}
	{b[0],b[1],b[2],....b[j-1]  |   b[j],b[j+1],...b[n-1]}
	*/
	int ans = INT_MIN;
	bool getAns = false;
	int l = 0, r = m;//必须是r=m，数组a是长度较小的一个，假如长度为0，那么m-1=-1，下面会直接出错
	int i = (l + r) / 2;
	int j = (m + n + 1) / 2 - i;
	while (l <= r)//同理，假如m==0，至少确保循环执行了一次
	{
		i = (l + r) / 2;//假如m为0，i为0
		j = (m + n + 1) / 2 - i;//+1很重要
		if (i > 0 && j<n && a[i - 1]>b[j])
			r = i - 1;
		else if (j > 0 && i<m && b[j - 1]>a[i])
			l = i + 1;
		else
		{
			if (i == 0)
				ans = b[j - 1];
			else if (j == 0)
				ans = a[i - 1];
			else
				ans = max(a[i - 1], b[j - 1]);
			break;
		}
	}
	cout << ans << endl;

	return 0;
}