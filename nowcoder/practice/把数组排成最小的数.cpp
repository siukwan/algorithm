/*
题目描述

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。
*/
class Solution {
public:

	int partition(vector<string>&s, int l, int r)
	{
		string pivot = s[r];
		int k = l;
		for (int i = l; i<r; ++i)
		{
			if (cmp(s[i], pivot))
				swap(s[k++], s[i]);
		}
		swap(s[r], s[k]);
		return k;
	}

	void quickSort(vector<string>&s, int l, int r)
	{
		if (l >= r) return;
		int k = partition(s, l, r);
		quickSort(s, l, k - 1);
		quickSort(s, k + 1, r);
	}

	bool cmp(string&a, string&b)
	{
		if (a[0] == b[0])
		{
			if (a + b<b + a)
				return true;
			else return false;
		}
		else
			return a<b;
	}
	string int2str(int a)
	{
		if (a == 0) return "0";
		string result = "";
		while (a != 0)
		{
			char c = a % 10 + '0';
			a = a / 10;
			result = c + result;
		}
		return result;
	}
	string PrintMinNumber(vector<int> numbers) {
		vector<string> str(numbers.size());
		for (unsigned int i = 0; i<numbers.size(); i++)
			str[i] = int2str(numbers[i]);

		quickSort(str, 0, str.size() - 1);

		string result = "";
		for (unsigned int i = 0; i<str.size(); i++)
			result += str[i];

		return result;
	}
};