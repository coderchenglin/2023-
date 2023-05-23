#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Stack
{
public:
	Stack(int capacity = 4);

	~Stack();

	void Push(const T& x);    //��ģ��  ͨ���Ƽ�ʹ��  �����ô���,�����Զ������͵Ŀ�������
	                                                                             //�ڲ��ı�������,�Ƽ�ʹ��const����

private:
	T* _a;
	int _capacity;
	int _top;
};

//
//int main()
//{
//	//��ģ�� ͳһ��ʾʵ����  ��Ϊһ��û�����ݵ�ʱ��
//	Stack<double> st1;
//	st1.Push(1.1);
//
//	Stack<int> st2;
//	st2.Push(2);
//}





















