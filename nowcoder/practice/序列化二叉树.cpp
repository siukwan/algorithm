/*
题目描述

请实现两个函数，分别用来序列化和反序列化二叉树
*/
/*
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};
*/
class Solution {
public:
	char* Serialize(TreeNode *root) {
		int address = 1;//根节点地址需要为1，因为需要通过正负的父地址来判断左右子树
		queue<pair<TreeNode*, int>> q;//first为节点，second为地址
		vector<pair<int, pair<int, int>>> arr(0);//first为val,second.first为父亲地址，second.second为自己地址
		int count1 = 0;
		int count2 = 0;
		if (root != NULL)
		{//根节点的父节点地址为1
			arr.push_back({ root->val, { INT_MAX, address } });
			q.push({ root, address });
			address++;
			count1++;
		}
		while (!q.empty())
		{
			//广度遍历树，记录每个节点的值，父节点地址，地址
			for (int i = 0; i < count1; i++)
			{
				pair<TreeNode*, int> head = q.front();
				q.pop();
				int parentAdd = head.second;//父亲节点的地址
				TreeNode* tmp = head.first;
				if (tmp->left != NULL)
				{//左儿子不为空
					arr.push_back({ tmp->left->val, { parentAdd, address } });
					q.push({ tmp->left, address });
					address++;
					count2++;
				}
				if (tmp->right != NULL)
				{//父节点为负数，表示是右儿子
					arr.push_back({ tmp->right->val, { -parentAdd, address } });
					q.push({ tmp->right, address });
					address++;
					count2++;
				}
			}
			count1 = count2;
			count2 = 0;
		}
		string result = "";//最终结果
		for (int i = 0; i < arr.size(); i++)
		{//格式为&val*parentAddress#address
			result += "&" + int2str(arr[i].first) + "*" + int2str(arr[i].second.first) + "#" + int2str(arr[i].second.second);
		}
		result;
		char* r = new char[result.size() + 1];
		int i = 0;
		for (i = 0; i<result.size(); ++i)
		{
			r[i] = result[i];
		}
		r[i] = 0;
		return r;
	}
	TreeNode* Deserialize(char *str) {
		string data = "";
		int i = 0;
		while (str[i] != 0)
			data += str[i++];
		map<int, TreeNode*> m;
		vector<pair<int, pair<int, int>>> arr(0);//还原成数组
		int process = -1;
		bool sign = true;
		int val = -1, parentAdd = INT_MAX, add = 0;
		for (int i = 0; i < data.size(); i++)
		{
			if (process == 0)
			{//此时检测的是val
				if (data[i] == '-')
					sign = false;
				else if (data[i] == '*')
				{
					if (!sign) val = -val;
					process++;
					sign = true;
				}
				else
					val = val * 10 + data[i] - '0';
			}
			else if (process == 1)
			{//此时检测的是parentAdd
				if (data[i] == '-')
					sign = false;
				else if (data[i] == '#')
				{
					if (!sign) parentAdd = -parentAdd;
					process++;
					sign = true;
				}
				else
					parentAdd = parentAdd * 10 + data[i] - '0';
			}
			else if (process == 2)
			{//此时检测的是add
				if (data[i] == '-')
					sign = false;
				else if (data[i] == '&')
					process = -1;
				else
					add = add * 10 + data[i] - '0';
			}
			//检测是否到了下一个开始
			if (process == -1 && data[i] == '&')
			{
				if (i != 0)
				{//如果i==0，初始值，不需要压入，i>0才需要
					if (!sign) add = -add;
					arr.push_back({ val, { parentAdd, add } });
				}
				sign = true;//初始化符号为正号
				val = 0;
				parentAdd = 0;
				add = 0;
				process++;
			}
		}
		//补充最后一个值
		if (data != "")
		{
			if (!sign) add = -add;
			arr.push_back({ val, { parentAdd, add } });
		}

		for (int i = 0; i < arr.size(); i++)
		{//把arr通过map还原成树
			int parentAdd = arr[i].second.first;
			int add = arr[i].second.second;
			int val = arr[i].first;
			m[add] = new TreeNode(val);
			if (parentAdd != INT_MAX)
			{
				if (parentAdd < 0)
					m[-parentAdd]->right = m[add];
				else
					m[parentAdd]->left = m[add];
			}
		}
		if (data != "")
			return m[1];
		else return NULL;
	}


	string int2str(int a)
	{
		bool sign = true;
		if (a < 0)
		{//注意负数情况
			sign = false;
			a = -a;
		}
		if (a == 0) return "0";
		string result = "";
		while (a != 0)
		{
			char c = a % 10 + '0';
			result = c + result;
			a /= 10;
		}
		if (!sign) result = "-" + result;
		return result;
	}
};