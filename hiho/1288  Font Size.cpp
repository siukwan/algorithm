#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <memory.h>
using namespace std;

int main()
{
	int t = 0;
	scanf("%d", &t);
	long long a[1001];
	while (t--)
	{
		memset(a, 0, sizeof(a));
		int n, p, w, h;
		scanf("%d%d%d%d", &n, &p, &w, &h);
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);

		int maxSize = min(w, h);
		bool flag = true;
		int size = maxSize;
		for (size = maxSize; size >= 1; size--)
		{
			flag = true;
			int eachLineWords = w / size;//每行能放的单词数量
			int lineWords = h / size;//每页能放的行数
			long long totalLine = p*lineWords;//一共能放的单词行数

			int sumCount = 0;
			int tmp = 0;
			for (int i = 0; i < n; ++i)
			{
				tmp = a[i] / eachLineWords;
				if (a[i] % eachLineWords != 0)
					sumCount += (tmp + 1);
				else
					sumCount += tmp;
				if (sumCount > totalLine)
					flag = false;
			}
			if (flag) break;
		}
		if (flag)
			printf("%d\n", size);
		else
			printf("%d\n", 0);
	}

	return 0;
}