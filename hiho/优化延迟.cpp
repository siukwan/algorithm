
//#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
#include<set>
#include<queue>
#include<map>
//#include<unordered_set>
#include<unordered_map>
//#include <sstream>
//#include "func.h"
//#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
#include<bitset>
//#include "siukwanAlloctor.h"
using namespace std;

long long arr[100002] = { 0 };
int size = 0;

long long pop()
{
	if (size == 0) return 0;
	long long result = arr[0];//获取栈顶元素
	long long x = arr[--size];//把队尾元素提到0号位置
	arr[size] = 0;
	int i = 0;
	int a = i * 2 + 1;//左孩子
	int b = i * 2 + 2;//右孩子

	while (a<size)
	{
		if (b<size&&arr[a]<arr[b])
			a = b;//右孩子比左孩子大
		if (x<arr[a])//孩子的值比父亲大，提上来
			arr[i] = arr[a];
		else//父亲的值比孩子大，停止操作
			break;
		i = a;
		a = i * 2 + 1;
		b = a + 1;
	}
	arr[i] = x;
	return result;
}
void push(long long x)
{
	int i = size++;
	int p = (i - 1) / 2;//父亲节点
	while (x>arr[p])
	{//孩子节点的值比父亲的值大
		arr[i] = arr[p];
		i = p;
		if (i == 0) break;
		p = (i - 1) / 2;
	}
	arr[i] = x;
}

int main()
{

	int n;
	long long quality;
	int data[100002] = { 0 };
	scanf("%d", &n);
	scanf("%ld", &quality);

	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &data[i]);
	}

	long long  sum = 0;
	int result = -1;
	int a = 1;
	int b = n;
	int mid = (a + b) / 2;
	while (a <= b)
	{
		memset(arr, 0, sizeof(arr));
		sum = 0;
		mid = (a + b) / 2;
		//建立大小为mid的堆
		int i = 0;
		int j = 1;//权重
		for (i = 0; i < mid; ++i)
		{
			push(data[i]);
		}

		//一个一个统计
		for (; i < n; ++i)
		{
			long long x = pop();//缓冲区已经满，把头部弹出来
			sum += x*(j++);
			push(data[i]);
		}
		while (size != 0)
		{
			long long x = pop();//缓冲区已经满，把头部弹出来
			sum += x*(j++);
		}

		if (sum <= quality)
			b = mid - 1;//尝试更小的空间
		else
			a = mid + 1;
		if (sum <= quality && (result == -1 || mid < result))
			result = mid;
	}
	cout << result << endl;

	return 0;
}