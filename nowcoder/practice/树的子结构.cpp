class Solution {
public:
	bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
	{
		//注意pRoot2为空也要返回false
		if (pRoot1 == NULL || pRoot2 == NULL) return false;
		int aLevel = level(pRoot1);
		int bLevel = level(pRoot2);

		//层序遍历找子结构
		queue<TreeNode*> q;
		int count1 = 0;
		int count2 = 0;
		int layer = 0;
		if (pRoot1 != NULL)
		{
			q.push(pRoot1);
			count1 = 1;
		}

		while (!q.empty())
		{
			for (int i = 0; i<count1; i++)
			{
				TreeNode* head = q.front();
				//进行比较
				if (isSame(head, pRoot2)) return true;
				q.pop();
				if (head->left)
				{
					count2++;
					q.push(head->left);
				}
				if (head->right)
				{
					count2++;
					q.push(head->right);
				}
			}
			count1 = count2;
			count2 = 0;
			layer++;
			//如果层数小于子树，直接返回false，提高效率
			if (aLevel - layer<bLevel) return false;
		}
		return false;
	}
	//求出树的层数
	int level(TreeNode* root)
	{
		queue<TreeNode*> q;
		int count1 = 0;
		int count2 = 0;
		int layer = 0;
		if (root != NULL)
		{
			q.push(root);
			count1 = 1;
		}

		while (!q.empty())
		{
			for (int i = 0; i<count1; i++)
			{
				TreeNode* head = q.front();
				q.pop();
				if (head->left)
				{
					count2++;
					q.push(head->left);
				}
				if (head->right)
				{
					count2++;
					q.push(head->right);
				}
			}
			count1 = count2;
			count2 = 0;
			layer++;
		}

		return layer;


	}
	bool isSame(TreeNode* a, TreeNode* b)
	{
		//如果b为空，则true
		if (b == NULL)
			return true;
		else if (a == NULL)
			return false;
		//两个都不为空
		else
		{
			//值不相等，false
			if (a->val != b->val)
				return false;
			else
			{
				//值相等，递归返回左右子树是否相等
				return isSame(a->left, b->left) && isSame(a->right, b->right);
			}
		}

	}
};