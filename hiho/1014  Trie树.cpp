//#include<string>  
//#include<stack>  
//#include<unordered_set>  
//#include <sstream>  
//#include "func.h"  
//#include <list>  
#include <iomanip>  
#include<unordered_map>  
#include<set>  
#include<queue>  
#include<map>  
#include<vector>  
#include <algorithm>  
#include<stdio.h>  
#include<iostream>  
#include<string>  
#include<memory.h>  
#include<limits.h>  
#include<stack>
using namespace std;

/*
5
babaab
babbbaaaa
abba
aaaaabaa
babaababb
5
babb
baabaaa
bab
bb
bbabbaab

5
babaab
babaab
babaab
babaab
babaab
5
babaab
babaab
babaab
babaab
babaab

*/
struct TrieNode{
	map<char, TrieNode*> child;
	int count;
	TrieNode(int x) :count(x){};
	TrieNode() :count(0){};
};
void insertWord(char *a, int pos, TrieNode*p)
{
	if (a[pos] == 0) return;//已经遍历完毕
	else
	{
		if (p->child.find(a[pos])!= p->child.end())
		{//找到有这个字母
			p->child[a[pos]]->count++;
			insertWord(a, pos + 1, p->child[a[pos]]);
		}
		else
		{//没找到，则新插入一个
			p->child[a[pos]] = new TrieNode(1);//默认count为1
			insertWord(a, pos + 1, p->child[a[pos]]);
		}
	}
}
int searchWord(char *a, int pos, TrieNode *p)
{

	if (p->child[a[pos]] != NULL)
	{//找到有这个字母
		if (a[pos+1]==0)
		return	p->child[a[pos]]->count;
		else return searchWord(a, pos + 1, p->child[a[pos]]);
	}
	else
	{//没找到，则新插入一个
		return 0;
	}
}
int main()
{
	TrieNode* root = new TrieNode(0);//建立一个根节点，不存储任何值，只用来连接第一个单词的字母，如单词acb和efg，a和e是root的儿子
	int n;//输入单词的个数
	scanf("%d", &n);
	char word[11];
	for (int i = 0; i < n; i++)
	{
		scanf("%s", word);
		insertWord(word, 0, root);
	}
	int querySum;//查询的次数
	scanf("%d", &querySum);
	for (int i = 0; i < querySum; i++)
	{
		scanf("%s", word);
		if (word[0] == 0) printf("0\n");
		else printf("%d\n", searchWord(word, 0, root));
	}
	return 0;
}

