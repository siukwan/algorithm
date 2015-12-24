//#include<string>
//#include <iomanip>
#include<fstream>
//#include<set>
//#include<queue>
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

/*
5 2 2
1 2 3 4 5
3 5
1 2
1 3
1 4
2 5
1.题目给出若干个村庄，和这些村庄的分数，给出需要参观的村庄的总数和一定参观的村庄，求出怎么安排参观的村庄以达到最大的分数。

2.这道题目实则是一个树形动态规划的题目，我们对题目进行转化的话，会得到：

选择一定需要参观的村庄的时候，它的父亲节点也必定选取。

我们首先建立状态f[i][k]，f[i][k]表示以i节点为根的子树，选择k个村庄能够得到的最大分数值。状态转移方程如下：

选择i村庄：f[i][k]等于村庄i的分数加上所有子节点选择k-1个节点的最大分数值
不选择i村庄：f[i][k] = 0
3.其中村庄的分数最大为100，村庄数量最多为100，所以总分最多是10000，我们给一定需要参观的村庄加上一个比较大的分数100000，这样，在动态规划的过程中，我们就会一定选取这些分数大的村庄（不一定全选，但是一旦可以到达，则必选）。

4.由于是树形，我们需要注意在统计子节点的分数时，不能反过来涉及到父节点，所以在添加边的时候，为单向边。

5.最终判断是否能够有solution时，我们判断f[1][k]/100000是否等于推荐参观村庄的数量，如果是，则输出f[1][k]，否则输出-1。

更详细的解答过程可以参考：http://siukwan.sinaapp.com/?p=820
*/


#define MOD 100000
struct VillageNode{
	int score;
	vector<int> nb;
	VillageNode() :score(0), nb(0){};
};
int dfs(vector<VillageNode>&village,vector<vector<int>>&f, int root, int k)
{
	if (k == 0)
		return 0;
	else if (f[root][k] != -1)
		return f[root][k];//如果之前已经计算过f[root][k]，则直接返回，不用遍历

	//不选择这个节点的时候
	f[root][k] = 0;

	//选择这个节点的时候
	
	int m = village[root].nb.size();
	
	//建立状态g[i][j]，g[i][j]表示前i个儿子选择j个节点时最大权值
	//g[i][j] = max{g[i - 1][j - t] + f[childId][t] | t = 0 .. j}
	vector<vector<int>> g(m + 1, vector<int>(k, 0));

	//枚举root的孩子节点，需要注意的是，枚举的是儿子节点，不能使用双向边
	for (int i = 1; i <= m; i++)
	{
		//因为选择当前节点，所以最多是求k-1个儿子的分值总和
		for (int j = 0; j < k; j++)
		{
			for (int t = 0; t <= j; t++)
			{
				int child = village[root].nb[i-1];
				if (g[i][j] < dfs(village, f, child, t) + g[i - 1][j - t])
				{
					g[i][j] = dfs(village, f, child, t) + g[i - 1][j - t];
				}
			}
		}
	}

	if (f[root][k] < g[m][k - 1] + village[root].score)
		f[root][k] = g[m][k - 1] + village[root].score;
	return f[root][k];

}
/*
函数名  ：main
函数功能：主函数
*/
int main(void)
{
	int villageCount;
	int recommendedVillageCount;
	int planCount;
	
	scanf("%d %d %d", &villageCount, &recommendedVillageCount, &planCount);
	
	vector<VillageNode> village(villageCount+1);
	//输入各个村庄的分数
	for (int i = 1; i <=villageCount; i++)
	{
		scanf("%d", &village[i].score);
	}

	//输入推荐的村庄
	for (int i = 0; i < recommendedVillageCount; i++)
	{
		int tmp;
		scanf("%d", &tmp);
		village[tmp].score += MOD;
	}

	//输入邻居关系
	for (int i = 0; i < villageCount - 1; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		village[a].nb.push_back(b);
		//需要注意的是，浏览的是儿子节点，不能使用双向边
		//village[b].nb.push_back(a);
	}

	vector<vector<int>>f(villageCount + 1, vector<int>(planCount + 1, -1));

	dfs(village, f, 1, planCount);
	if (f[1][planCount] / MOD == recommendedVillageCount)
		printf("%d\n", f[1][planCount] % MOD);
	else
		printf("-1\n");


	return  0;
}
