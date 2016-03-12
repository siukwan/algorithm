
//10000以内的完数只有4个，6，28，496，8128
#include<stdio.h>
#include<set>
#include<vector>
using namespace std;
set<int> getFactor(int n)
{
	set<int> result;
	if (n != 0) result.insert(1);
	for (int i = 2; i*i <= n; ++i)
	{
		if (n%i == 0)
		{
			result.insert(i);
			result.insert(n / i);
		}
	}
	return result;
}

int getSum(set<int>& s)
{
	int result = 0;
	for (auto ite = s.begin(); ite != s.end(); ++ite)
		result += *ite;
	return result;
}

int main()
{
	vector<bool> table(10001, false);
	for (int i = 2; i < table.size(); ++i)
	{
		if (i != 1 && getSum(getFactor(i)) == i)
			table[i] = true;
	}
	int n, l, r;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d%d", &l, &r);
		if (l>r)
		{
			l ^= r;
			r ^= l;
			l ^= r;
		}
		int result = 0;
		for (int i = l; i <= r; ++i)
		{
			if (table[i])
				result++;
		}
		printf("%d\n", result);
	}
	return 0;
}