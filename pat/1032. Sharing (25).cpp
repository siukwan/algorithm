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
11111 22222 9
67890 i 00002
00010 a 12345
00003 g -1
12345 D 67890
00002 n 00003
22222 B 23456
11111 L 00001
23456 e 67890
00001 o 00010

11111 22222 9
00012 i 00002
00010 a 12345
00003 g -1
12345 D 00012
00002 n 00003
22222 B 23456
11111 L 00001
23456 e 00012
00001 o 00010
*/
int main(void)
{
	int *m = new int[100001];
	int *exist = new int[100001];
	memset(m, -1, sizeof(m));
	memset(exist, -1, sizeof(exist));
	int sum;
	int a, b;
	scanf("%d %d %d", &a, &b, &sum);
	m[a] = -1;
	m[b] = -1;

	for (int i = 0; i < sum; i++)
	{
		char tmp[10];
		int pre, next;
		scanf("%d %s %d", &pre, tmp, &next);
		m[pre] = next;
	}
	int head = a;
	while (head != -1)
	{//把第一个链表存进哈希表 exist中
		exist[head] = 1;
		head = m[head];
	}
	head = b;
	while (head != -1)
	{
		if (exist[head] == 1)
		{
			break;
		}
		head = m[head];
	}
	if (head != -1)
		printf("%05d\n", head);
	else
		printf("%d\n", head);

	return 0;
}