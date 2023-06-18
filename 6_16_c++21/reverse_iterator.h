#pragma once
#include <iostream>
#include<list>

//template <typename T>
//class ReverseIterator
//{
//public:
//	//定义迭代器类型别名
//	//using iterator_
//
//	//构造函数
//	ReverseIterator(T* ptr)
//		:ptr_(ptr)
//	{}
//
//	ReverseIterator& operator++()
//	{
//		--ptr_;
//		return *this;
//	}
//
//	ReverseIterator operator++(int)
//	{
//		ReverseIterator tmp = *this;
//		--ptr_;
//		return tmp;
//	}
//
//	ReverseIterator& operator--()
//	{
//		++ptr_;
//		return *this;
//	}
//
//	ReverseIterator operator--(int)
//	{
//		ReverseIterator tmp = *this;
//		++ptr_;
//		return tmp;
//	}
//
//	T& operator*() const
//	{
//		return *--ptr_;
//	}
//
//	T* operator->() const
//	{
//		return ptr_;
//	}
//
//	bool operator==(const ReverseIterator& rhs) const
//	{
//		return ptr_ == rhs.ptr_;
//	}
//
//	bool operator!=(const ReverseIterator& rhs) const
//	{
//		return !(*this == rhs);
//	}
//
//
//
//
//private:
//	T* ptr_;
//};
//
//

//给我不同容器的正向迭代器,适配出对应的这个容器需要的反向迭代器 -- 只要能够支持operator--就行
template<class Iterator,class Ref,class Ptr>
class ReverseIterator
{
	Typedef ReverseIterator<Iterator, Ref, Ptr> Self;
public:
	ReverseIterator(iterator it)
		:_it(it)
	{}

	Ref operator*()
	{
		Iterator tmp = _it;
		return *(--tmp);
	}

	Ptr operator->()  // -> 返回的是一个地址    在外面真正使用时,编译器你会将->转换成->->
	{
		return &(operator*());
	}

	Self& operator++()  //这个++是用来支持迭代器的
	{
		--_it;
		return *this;
	}

	Self& operator--()
	{
		++_it;
		return *this;
	}

	bool operator!=(const Self& s) const
	{
		return _it != s._it;
	}

private:
	Iterator _it;
};

















