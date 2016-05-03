//#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
#include<set>
#include<queue>
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
using namespace std;
int main(void) {
	//精度要求，使用double或者float都可以AC
	vector<vector<double>> game(3, vector<double>(3, 0));
	string s[3] = { "W", "T", "L" };
	scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf", &game[0][0], &game[0][1], &game[0][2], &game[1][0], &game[1][1], &game[1][2], &game[2][0], &game[2][1], &game[2][2]);

	double ans[3];
	string out[3];
	ans[0] = game[0][0];
	ans[1] = game[1][0];
	ans[2] = game[2][0];
	out[0] = s[0];
	out[1] = s[0];
	out[2] = s[0];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 3; j++)
		{
			if (ans[i] < game[i][j])
			{
				ans[i] = game[i][j];
				out[i] = s[j];
			}
		}
	}
	double res = (ans[0] * ans[1] * ans[2] * 0.65 - 1) * 2;
	res += 0.00000001;
	cout << out[0] << " " << out[1] << " " << out[2] << " ";
	printf("%.2lf\n", res);

	return 0;
}