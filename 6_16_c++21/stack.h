#pragma once

//适配器模式 - 用现有的东西,封装转化出我们想要的东西
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

	//stack<int, vector<int>> st1; //用vector来实现栈
	//stack<int, list<int>> st2;   //用list来实现栈

	template<class T, class Container = vector<T>>  //T是数据类型, Container是容器类型
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

//T是数据类型,Container是容器类型
//Container - vector/list
//T - int/char/double

