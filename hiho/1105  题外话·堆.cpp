#include<stdio.h>

int arr[100002] = { 0 };
int size = 0;

int pop()
{
	if (size == 0) return 0;
	int result = arr[0];//获取栈顶元素
	int x = arr[--size];//把队尾元素提到0号位置
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
void push(int x)
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
	scanf("%d", &n);
	while (n--)
	{
		char c[10];
		scanf("%s", c);
		if (*c == 'A')
		{
			int x;
			scanf("%d", &x);
			push(x);
		}
		else
			printf("%d\n", pop());
	}
	return 0;
}