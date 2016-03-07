
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
//#include "siukwanAlloctor.h"
using namespace std;
//分配对齐地址的指针
void * aligned_malloc(int size, int alignment)
{
	void* ptr = malloc(size + alignment);

	if (ptr)
	{
		//注意是加上alignment后在取与，与stl中的简单向上取整不一样，stl中的向上取整是加上（alignment-1）
		//这里加上alignment，能确保aligned前面的地址空间存在空白部分
		void* aligned = (void*)(((long)ptr + alignment) & ~(alignment - 1));
		((void**)aligned)[-1] = ptr;//相当于*(aligned-1)的意思，由于语法错误，需要强制转换类型，意思是把ptr存放在aligned-1指向的地址的空间中

		return aligned;
	}
	else
		return NULL;
}
//释放函数aligned_free
void aligned_free(void *paligned)
{
	//删除相应的地址空间
	free(((void**)paligned)[-1]);
}
int main()
{

	int *p = (int*)aligned_malloc(sizeof(int), 8);
	cout << p << endl;
	aligned_free(p);
	return 0;
}