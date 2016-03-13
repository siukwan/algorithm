#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
int price[51];
int desire[51];
int main()
{

	int q, n;
	scanf("%d", &q);
	while (q--)
	{
		//memset(snacks,0,sizeof(int)*51*2);
		scanf("%d", &n);

		for (int i = 0; i<n; ++i)
		{
			float a;
			int b;
			scanf("%f %d", &a, &desire[i]);
			price[i] = a * 2;
		}
		int result = 0;
		for (int i = 0; i<n; ++i)
		{
			for (int j = i + 1; j<n; ++j)
			{
				for (int k = j + 1; k<n; ++k)
				{
					int sum = price[i] + price[j] + price[k];
					if (sum % 10 == 0)
						result = max(desire[i] + desire[j] + desire[k], result);
				}
			}
		}
		for (int i = 0; i<n; ++i)
		{
			for (int j = i + 1; j<n; ++j)
			{
				int sum = price[i] + price[j];
				if (sum % 10 == 0)
					result = max(desire[i] + desire[j], result);
			}
		}
		for (int i = 0; i<n; ++i)
		{
			int sum = price[i];
			if (sum % 10 == 0)
				result = max(desire[i], result);
		}
		printf("%d\n", result);

	}
	return 0;
}