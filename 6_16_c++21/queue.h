#pragma once
#include<vector>
#include<list>


namespace lp
{
	template<class T, class Container = list<T>>  //T是数据类型, Container是容器类型
	class queue
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_front();
		}

		const T& front()
		{
			return _con.front();
		}

		const T& back()
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


