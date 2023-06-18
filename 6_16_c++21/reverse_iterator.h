#pragma once
#include <iostream>
#include<list>

//template <typename T>
//class ReverseIterator
//{
//public:
//	//������������ͱ���
//	//using iterator_
//
//	//���캯��
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

//���Ҳ�ͬ���������������,�������Ӧ�����������Ҫ�ķ�������� -- ֻҪ�ܹ�֧��operator--����
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

	Ptr operator->()  // -> ���ص���һ����ַ    ����������ʹ��ʱ,��������Ὣ->ת����->->
	{
		return &(operator*());
	}

	Self& operator++()  //���++������֧�ֵ�������
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

















