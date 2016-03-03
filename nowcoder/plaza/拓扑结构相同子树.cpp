/*
对于两棵彼此独立的二叉树A和B，请编写一个高效算法，检查A中是否存在一棵子树与B树的拓扑结构完全相同。
给定两棵二叉树的头结点A和B，请返回一个bool值，代表A中是否存在一棵同构于B的子树

*/

//前序遍历+KMP

/*
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};*/
class IdenticalTree {
public:
	bool chkIdentical(TreeNode* A, TreeNode* B) {
		// write code here
		if (B == NULL) return true;
		else if (A == NULL) return false;
		vector<int> pattern;
		vector<int> str;

		dfs(A, str);
		dfs(B, pattern);

		if (str.size()<pattern.size()) return false;

		//构建next数组
		vector<int> next(pattern.size() + 1, 0);

		for (int i = 1; i<pattern.size(); ++i)
		{
			int j = next[i];
			while (j>0 && pattern[i] != pattern[j])
				j = next[j];

			if (pattern[i] == pattern[j])
				next[i + 1] = j + 1;//求next[i+1]的值，所以比较的是p[i]和p[j]

		}

		//使用KMP
		int j = 0;
		for (int i = 0; i<str.size(); ++i)
		{
			while (j>0 && str[i] != pattern[j])
				j = next[j];

			if (str[i] == pattern[j])
				j++;//比较下一个值

			if (j == pattern.size())
			{
				//匹配到字串了，返回真
				return true;
			}
		}

		//没找到，false
		return false;


	}
	//进行前序遍历
	void dfs(TreeNode* root, vector<int>&preOrder)
	{
		if (root == NULL){
			//需要加上叶子节点
			preOrder.push_back(INT_MAX);
			return;
		}
		preOrder.push_back(root->val);
		dfs(root->left, preOrder);
		dfs(root->right, preOrder);
	}
};