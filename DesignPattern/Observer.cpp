//C++实现观察者模式

#include<vector>
#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

template <class Handler>
class event //模板类，这就决定了这个委托可以委托任何类型了函数指针，只要你有，我就能委托  
{
public:
	event()
	{//构造函数
	}
	vector<Handler>& GetEvent()
	{//获取Event列表
		return m_HandlerList;
	}
	virtual void add(const Handler v)
	{//虚函数，添加时间到vector中
		m_HandlerList.push_back(v);
	}
	virtual void remove(const Handler v)
	{//删除vector
		vector<Handler>::iterator it = m_HandlerList.begin();
		for (; it != m_HandlerList.end(); it++)
		{
			if ((*it) == v)
			{//如果相等，则删除
				m_HandlerList.erase(it);
				break;
			}
		}
	}
private:
	vector<Handler> m_HandlerList;//时间列表
};

//参数列表为空，EventHandler是函数地址
typedef void   (*EventHandler)(void);
class MyClass
{
public:
	MyClass(){}
	void Notify()
	{
		size_t nCount = AllEvent.GetEvent().size();
		for (size_t i = 0; i < nCount; i++)
		{
			EventHandler notifyEvent = AllEvent.GetEvent()[i];
			(*notifyEvent)();

			//另外的两种写法
			//(*(AllEvent.GetEvent().at(i)))();
			//(*(AllEvent.GetEvent()[i]))();
		}
	}
public:
	event <EventHandler> AllEvent;
};


void MyEventHandler1()
{
	printf("This is a event!\n");
}
void MyEventHandler2()
{
	printf("This is another event!\n");
}

int main(void)
{

	MyClass Obj;
	Obj.AllEvent.add(MyEventHandler1);
	Obj.AllEvent.add(MyEventHandler2);
	Obj.Notify();
	Obj.AllEvent.remove(MyEventHandler1);
	Obj.Notify();
	printf("Over!\n");
	system("pause");
	return 0;


}