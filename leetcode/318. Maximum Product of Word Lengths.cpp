class Solution {
public:
	int maxProduct(vector<string>& words) {
		unordered_map<int, int> mask;
		for (int i = 0; i<words.size(); ++i)
		{
			int tmpMask = 0;
			for (int j = 0; j<words[i].size(); ++j)
				tmpMask |= 1 << (words[i][j] - 'a');
			mask[tmpMask] = max(mask[tmpMask], (int)words[i].size());
		}
		int result = 0;
		for (auto word1 = mask.begin(); word1 != mask.end(); ++word1)
		{
			for (auto word2 = mask.begin(); word2 != word1; ++word2)
				if (!(word1->first&word2->first))
					result = max(result, word1->second*word2->second);
		}
		return result;
	}
};