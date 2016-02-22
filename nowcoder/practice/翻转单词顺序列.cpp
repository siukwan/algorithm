/*
题目描述

牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student. a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？

*/
class Solution {
public:
	string ReverseSentence(string str) {
		str += " ";
		int start = 0;
		for (int i = 0; i<str.size(); ++i)
		{
			if (str[i] == ' ')
			{
				for (int j = start; j<start + (i - start) / 2; ++j)
					swap(str[j], str[i - 1 - j + start]);

				start = i + 1;
			}
		}
		str = str.substr(0, str.size() - 1);
		for (int i = 0; i<str.size() / 2; ++i)
			swap(str[i], str[str.size() - 1 - i]);
		return str;
	}
};