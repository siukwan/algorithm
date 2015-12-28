/*
直线与圆的关系
现在有一条直线和一个圆。请写一个程序判断它们的位置关系。其中0代表直线和圆相离，1代表两者相切，2代表两者相交。
给定直线上的两个点(不重合)的坐标x1,y1,x2,y2,另外给定圆心坐标xc,yc和圆的半径r。请返回判断的结果(0或1或2)。
测试样例：
-1,-1,1,1,0,0,2
返回：2

时间限制:
1秒

内存限制:
32768KB
*/
#include<string>
#include <iomanip>
#include<fstream>
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
//#include<stack>
#include<vector>
#include <algorithm>
using namespace std;

class LineAndCircle {
public:

	double cmpzero(double x)
	{
		double eps = 1e-9;
		return fabs(x)<eps ? 0 : x;
	}
	int judgeStat(double x1, double y1, int x2, int y2, int xc, int yc, int r) {
		set<pair<double, double>> p;
		double X0 = xc, Y0 = yc;
		double X1 = x1, Y1 = y1;
		double X2 = x2, Y2 = y2;
		double R = r;
		double DX = X2 - X1, DY = Y2 - Y1;
		double A = DX*DX + DY*DY;
		double B = 2 * DX*(X1 - X0) + 2 * DY*(Y1 - Y0);
		double C = (X1 - X0)*(X1 - X0) + (Y1 - Y0)*(Y1 - Y0) - R*R;
		double DELTA = B*B - 4 * A*C;
		int num = 0;
		if (cmpzero(DELTA)>= 0)
		{
			double T1 = (-B - sqrt(DELTA)) / (2 * A);
			double T2 = (-B + sqrt(DELTA)) / (2 * A);
			//if (cmpzero(T1 - 1) <= 0 && cmpzero(T1) >= 0)
				p.insert({ X1 + T1*DX, Y1 + T1*DY });
			//if (cmpzero(T2 - 1) <= 0 && cmpzero(T2) >= 0)
				p.insert({ X1 + T2*DX, Y1 + T2*DY });
		}
		return p.size();
	}
};

int main()
{
	LineAndCircle t;
	cout << t.judgeStat(-1, -2, 2, -2, 0, 0, 0) << endl;
	return 0;
}
