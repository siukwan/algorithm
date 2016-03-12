/*
在一组数的编码中，若任意两个相邻的代码只有一位二进制数不同， 则称这种编码为格雷码(Gray Code)，请编写一个函数，使用递归的方法生成N位的格雷码。
给定一个整数n，请返回n位的格雷码，顺序为从0开始。
测试样例：
1
返回：["0","1"]
*/
class GrayCode {
public:
	vector<string> getGray(int n) {
		// write code here
		vector<string> gray;
		if (n == 0) return gray;
		gray.push_back("0");
		gray.push_back("1");
		span(gray, n - 1);
		return gray;

	}

	void span(vector<string>&gray, int n)
	{
		if (n == 0) return;
		int size = gray.size();
		for (int i = size - 1; i >= 0; --i)
		{
			gray.push_back("1" + gray[i]);
			gray[i] = "0" + gray[i];
		}
		span(gray, n - 1);
	}
};