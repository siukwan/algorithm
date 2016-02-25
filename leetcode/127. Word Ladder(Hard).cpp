/*

1.分析题目后，我们发现需要找出一条路径，而这条路径的限制是每次只改变一个字母。因此，这也可以理解为求单元最短路径。

2.我们可以考虑采用DFS或者BFS进行搜索。先看看DFS，DFS每次找出一条到达目标点的路径，但是不确定这条路径是否为最短，所以需要遍历完所有的节点才确定到最终解。

3.而BFS相当于一层一层地往外搜索，所以一旦遇到目标点，那么其记录的路径长度就是最短长度，经过上面的分析，我们可以初步使用BFS进行求解。

4.最初的思路是构建好各个单词的邻居，要构建邻居关系，需要对每个单词遍历一次单词表，时间复杂度为O(n*n)，而BFS的复杂度为O(n)，实际我刚开始也是这么做的，结果超时了。单词量能上到2000以上。

5.为了解决构建邻居超时的问题，我换了一种方法，就是事先不构建邻居，而是在BFS中，通过原来的单词进行字母变换，构建出一个新单词，再去判断这个单词是否在wordList中，假设单词长度为k，每个字母替换26次，BFS的复杂度为O(n)，则总的复杂度为（26*k*n）。这样编写程序能够顺利通过测试，耗时460ms。
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#include <unordered_set>
using namespace std;

class Solution {
public:

	int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
		map<string, bool> visited;
		int wordSize = beginWord.size();

		int length = 1;
		queue<string> q;
		q.push(beginWord);
		visited[beginWord] = true;
		int count1 = 1;
		int count2 = 0;

		while (!q.empty())
		{
			length++;
			for (int i = 0; i < count1; ++i)
			{
				string head = q.front();
				q.pop();
				string tmp = head;

				//替换每个单词的每个字母，看看是否能够在wordList中找到
				for (int j = 0; j < wordSize; ++j)
				{
					tmp = head;
					for (int k = 0; k < 26; k++)
					{
						tmp[j] = 'a' + k;
						if (wordList.find(tmp) != wordList.end() && !visited[tmp])
						{//找到邻居
							visited[tmp] = true;
							q.push(tmp);
							count2++;
						}
						if (tmp == endWord)
							return length;
					}
				}
			}
			count1 = count2;
			count2 = 0;
		}
		return 0;

	}
};
int main(void)
{
	string a = "4";
	string b = "321";
	if (a>b) cout << 1 << endl;
	else
		cout << 2 << endl;
	unordered_set<string> w = { "hot", "dot", "dog", "lot", "log" };
	Solution sols;
	cout << sols.ladderLength("hit", "cog", w) << endl;
	return 0;
}
