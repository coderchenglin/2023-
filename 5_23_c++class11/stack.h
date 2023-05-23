#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Stack
{
public:
	Stack(int capacity = 4);

	~Stack();

	void Push(const T& x);    //类模板  通常推荐使用  传引用传参,减少自定义类型的拷贝构造
	                                                                             //在不改变的情况下,推荐使用const引用

private:
	T* _a;
	int _capacity;
	int _top;
};

//
//int main()
//{
//	//类模板 统一显示实例化  因为一般没有推演的时机
//	Stack<double> st1;
//	st1.Push(1.1);
//
//	Stack<int> st2;
//	st2.Push(2);
//}





















