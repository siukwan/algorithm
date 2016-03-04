/*

int main(void)
{
int ia[5] = { 0, 1, 2, 3, 4 };

vector<int, siukwan::allocator<int>> iv(ia, ia + 5);
return 0;


}
*/



#ifndef _SIUKWANALLOC_
#define _SIUKWANALLOC_

#include<new>
#include<cstddef>  //ptrdiff_t,size_t
#include<cstdlib>  //exit()
#include<climits>  //UINT_MAX
#include<iostream> //cerr

namespace siukwan
{
	template<class T>
	inline T* _allocate(ptrdiff_t size, T*)
	{
		set_new_handler(0);

		//::operator new返回的指针类型是void*，需要转换成T*类型
		T* tmp = (T*)(::operator new((size_t)(sizeof(T)*size)));

		if (tmp == 0)
		{//分配失败
			cerr << "out of memory" << endl;
			exit(1);
		}
		return tmp;
	}

	template<class T>
	inline void _deallocate(T* buffer)
	{
		::operator delete(buffer);
	}

	template<class T1,class T2>
	inline void _construct(T1* p, const T2&value)
	{
		new(p) T1(value);
		//p = new T1();//不能这样写，这样无法为p申请地址
		//*p = value;
	}

	template<class T>
	inline void _destroy(T* ptr)
	{
		ptr->~T();//调用析构函数
	}


	//配置器
	template <class T>
	class allocator{
	public:
		typedef T   value_type;
		typedef T*   pointer;
		typedef const T* const_pointer;
		typedef T&    reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		//把T类型重新绑定为U类型
		template<class U>
		struct rebind{
			typedef allocator<U> other;
		};

		//
		pointer allocate(size_type n, const void* hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}

		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		void construct(pointer p, const T&value)
		{
			_construct(p, value);
		}
		void destroy(pointer p)
		{
			_destroy(p);
		}

		pointer address(reference x)
		{
			return (pointer)&x;
		}

		const_pointer const_address(const_reference x)
		{
			return (const_pointer)&x;
		}

		size_type max_size() const{
			return size_type(UINT_MAX / sizeof(T));
		}
	};
}

#endif