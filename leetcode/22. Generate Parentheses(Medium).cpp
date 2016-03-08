class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> result;
		dfs(result, "", n, 0);
		return result;
	}

	void dfs(vector<string>&result, string str, int n, int right)
	{
		if (n == 0)//括号已经用完了
		{
			while (right>0)//右括号还有
			{
				str += ')';
				right--;
			}
			result.push_back(str);
		}
		else
		{
			//添加'(''
			dfs(result, str + '(', n - 1, right + 1);

			//添加'(''
			if (right>0)
				dfs(result, str + ')', n, right - 1);
		}

	}
};
};