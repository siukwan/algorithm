/*
子网掩码是用来判断任意两台计算机的IP地址是否属于同一子网络的根据。
子网掩码与IP地址结构相同，是32位二进制数，其中网络号部分全为“1”和主机号部分全为“0”。利用子网掩码可以判断两台主机是否中同一子网中。若两台主机的IP地址分别与它们的子网掩码相“与”后的结果相同，则说明这两台主机在同一子网中。
示例：
I P 地址　 192.168.0.1
子网掩码　 255.255.255.0
转化为二进制进行运算：
I P 地址　11010000.10101000.00000000.00000001
子网掩码　11111111.11111111.11111111.00000000
AND运算
　　　　11000000.10101000.00000000.00000000
	转化为十进制后为：
	　　　　192.168.0.0

		I P 地址　 192.168.0.254
		子网掩码　 255.255.255.0

		转化为二进制进行运算：
		I P 地址　11010000.10101000.00000000.11111110
		子网掩码　11111111.11111111.11111111.00000000
		AND运算
		　　　　　11000000.10101000.00000000.00000000
			 转化为十进制后为：
			 　　　　　192.168.0.0
				  通过以上对两台计算机IP地址与子网掩码的AND运算后，我们可以看到它运算结果是一样的。均为192.168.0.0，所以这二台计算机可视为是同一子网络。
				  /*
				  * 功能: 判断两台计算机IP地址是同一子网络。
				  * 输入参数：    String Mask: 子网掩码，格式：“255.255.255.0”；
				  *               String ip1: 计算机1的IP地址，格式：“192.168.0.254”；
				  *               String ip2: 计算机2的IP地址，格式：“192.168.0.1”；
				  *
				  * 返回值：      0：IP1与IP2属于同一子网络；     1：IP地址或子网掩码格式非法；    2：IP1与IP2不属于同一子网络
				  */
public int checkNetSegment(String mask, String ip1, String ip2)
{
	/*在这里实现功能*/
	return 0;
}


输入描述:

输入子网掩码、两个ip地址


输出描述 :

得到计算结果

输入例子 :

255.255.255.0
192.168.224.256
192.168.10.4

输出例子 :

	 1

*/



//#include<string>
//#include <iomanip>
#include<vector>
#include <algorithm>
//#include<stack>
#include<set>
#include<queue>
#include<map>
//#include<unordered_set>
#include<unordered_map>
//#include <sstream>
//#include "func.h"
//#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
#include<bitset>
using namespace std;

/*

255.0
193.194.202.15
232.43.7.59

输出2

*/
void str2int(string &str, int ip[4])
{
	str += ".";
	int a = 0;
	int k = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == '.')
		{
			ip[k++] = a;
			a = 0;
		}
		else
			a = a * 10 + str[i] - '0';
	}
	for (int i = k; i < 4; ++i)
	{
		ip[i] = 0;
	}

}

int main(void)
{

	int ip[3][4];
	string str = "";
	while (getline(cin, str))
	{
		str2int(str, ip[0]);
		getline(cin, str);
		str2int(str, ip[1]);
		getline(cin, str);
		str2int(str, ip[2]);

		bool format = true;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (ip[i][j] < 0 || ip[i][j]>255)
				{
					printf("1\n");
					format = false;
					break;
				}
			}
		}
		if (!format) continue;

		bool flag = true;
		for (int i = 0; i < 4; ++i)
		{
			if ((ip[0][i] & ip[1][i]) != (ip[0][i] & ip[2][i]))
			{
				flag = false;
				break;
			}
		}
		if (flag) printf("0\n");
		else printf("2\n");
	}
	return 0;
}