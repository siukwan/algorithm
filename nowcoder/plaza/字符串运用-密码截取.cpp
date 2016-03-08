/*
Catcher是MCA国的情报员，他工作时发现敌国会用一些对称的密码进行通信，比如像这些ABBA，ABA，A，123321，但是他们有时会在开始或结束时加入一些无关的字符以防止别国破解。比如进行下列变化 ABBA->12ABBA,ABA->ABAKK,123321->51233214　。因为截获的串太长了，而且存在多种可能的情况（abaaab可看作是aba,或baaab的加密形式），Cathcer的工作量实在是太大了，他只能向电脑高手求助，你能帮Catcher找出最长的有效密码串吗？


输入描述:

输入一个字符串


输出描述:

返回有效密码串的最大长度

输入例子:

ABBA

输出例子:

4
*/

//前序遍历+KMP

#include<string>
#include<iostream>
#include<vector>

using namespace std;

int manacher(string tmp)
{
	//插入字符串，得到一个新串
	string s = "$";
	for (int i = 0; i<tmp.size(); ++i)
	{
		s += "#";
		s += tmp[i];
	}
	s += "#";

	int id = 0;//拥有最大回文边界的位置
	int mx = 0;//最大的回文边界
	vector<int> p(s.size(), 0);

	for (int i = 1; i<s.size(); ++i)
	{
		//根据以前的数据计算出暂时最大的p[i]
		if (mx>i)
		{
			p[i] = min(p[2 * id - i], mx - i);
		}
		else
			p[i] = 1;

		//朴素检测
		while (s[i - p[i]] == s[i + p[i]])
		{
			p[i]++;
		}

		//更新id和mx
		if (i + p[i]>mx)
		{
			mx = i + p[i];
			id = i;
		}
	}

	int result = -1;
	for (int i = 0; i<p.size(); ++i)
	{
		result = max(p[i] - 1, result);
	}
	return result;
}

int main()
{
	string s;
	while (cin >> s)
		cout << manacher(s) << endl;
	return 0;
}