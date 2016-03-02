/*
编写一个函数，确定需要改变几个位，才能将整数A转变成整数B。
给定两个整数int A，int B。请返回需要改变的数位个数。
测试样例：
10,5
返回：4

*/
class Transform {
public:
	int calcCost(int A, int B) {
		// write code here
		int y = 1;
		int result = 0;
		for (int i = 0; i<32; ++i)
		{
			int a = (y&A);
			int b = (y&B);
			if (a != b)
				result++;
			y = y << 1;
		}
		return result;
	}
};