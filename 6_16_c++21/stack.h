#pragma once

//������ģʽ - �����еĶ���,��װת����������Ҫ�Ķ���
#include <vector>
#include <list>


namespace lp
{
	//template<class T>
	//class stack
	//{
	//private:
	//	T* _a;
	//	int _top;
	//	int _capacity;
	//};

	//stack<int, vector<int>> st1; //��vector��ʵ��ջ
	//stack<int, list<int>> st2;   //��list��ʵ��ջ

	template<class T, class Container = vector<T>>  //T����������, Container����������
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}

		T& top()
		{
			return _con.back();
		}

		bool empty()
		{
			return _con.empty();
		}

		size_t size()
		{
			return _con.size();
		}

	private:
		Container _con;

	};

}

//T����������,Container����������
//Container - vector/list
//T - int/char/double

