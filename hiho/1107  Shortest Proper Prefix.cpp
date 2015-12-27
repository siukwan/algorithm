/*
题目：
1.题目涉及到了一个proper prefix和shortest proper prefix。
2.proper prefix是指真前缀，即包含这个前缀的单词小于等于5个。
3.shortest proper prefix是指最短真前缀，是指除了它之外的前缀（可以理解为比它长的前缀）都不是真前缀。
所以我们要求出这样一个集合：
（1）集合中任意前缀对应的单词数量小于等于5；
（2）对于集合中任意前缀p，p的扩展前缀不属于该集合。

这是一道Trie的题目，需要建立Trie树。
我采用了map<char,Trie*> child的结构存储子节点。
在建立树的过程中，通过单词个数，最后进行深度搜索（或者广度搜索），找出<=5的节点的个数，需要注意的是，如果节点的count<=5，则不再遍历它的儿子节点，否则需要遍历它的儿子节点。

问题所在：
1.为了提高速度，我是用了char数组和scanf进行输入。
2.之前我分配的char数组大小为1000、10000、100000，均会出现Runtime Error（RE错误）。
3.然后我把代码放到hiho第七十八周的挑战赛上，发现能够得分60，但是仍然RE错误，证明部分测试用例是正确的。
4.接着我把char数组改成string输入，再提交，发现得分能够到达70分，但是错误已经变成TLE，超时错误。
5.于是我开始测试是不是char数组大小不满足要求，把数组大小改为1000000，即100万的长度，终于AC了。

*/
/*
*/

#include<string>
#include <iomanip>
#include<fstream>
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
//#include<stack>
#include<vector>
#include <algorithm>
using namespace std;

struct Trie{
	map<char, Trie*> child;
	int count;
	Trie() :count(0){};
	Trie(int x) :count(x){};
};

void InsertWord(char *a, int pos, Trie*p)
{
	if (a[pos] == 0) return;//已经遍历完毕
	else
	{
		if (p->child.find(a[pos]) != p->child.end())
		{//找到有这个字母
			p->child[a[pos]]->count++;
			InsertWord(a, pos + 1, p->child[a[pos]]);
		}
		else
		{//没找到，则新插入一个
			p->child[a[pos]] = new Trie(1);//默认count为1
			InsertWord(a, pos + 1, p->child[a[pos]]);
		}
	}
}
void dfs(int &ans, Trie* root)
{
	if (root->count <= 5)
		ans++;
	else if (root->child.size())
	{
		for (map<char, Trie*>::iterator ite = root->child.begin(); ite != root->child.end(); ite++)
		{
			dfs(ans, ite->second);
		}
	}
}
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int n;
	Trie *root = new Trie;
	root->count = INT_MAX;
	char *word = new char[1000000];
	memset(word, 0, 1000000);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		memset(word, 0, 1000000);
		scanf("%s", word);
		InsertWord(word, 0, root);
	}
	int ans = 0;
	dfs(ans, root);

	cout << ans << endl;

	return  0;
}
