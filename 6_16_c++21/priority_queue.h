#pragma once

//#include<iostream>
//#include<vector>

//using namespace std;

namespace lp
{
	template<class T,class Container = vector<T>>
	class priority_queue
	{
	public:
		priority_queue()
		{}

		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
			:_con(first,last) //在初始化列表直接调用 vector 的构造函数
		{
			//建堆
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; --i)
			{
				adjust_down(i);
			}

		}
		//向上调整
		void adjust_up(size_t child)
		{
			size_t parent = (child - 1) / 2;
			while(child > 0)
			{
				if (_con[child] > _con[parent])
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);

			adjust_up(_con.size() - 1);
		}

		//向下调整
		void adjust_down(size_t parent)
		{
			size_t child = parent * 2 + 1; //假设左孩子大
			while (child < _con.size())
			{
				if (child + 1 < _con.size() && _con[child + 1] > _con[child])
				{
					child++;
				}

				if (_con[child] > _con[parent])
				{
					swap(_con[child],_con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}

		}

		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();

			adjust_down(0);
		}

		const T& top() const
		{
			return _con[0];
		}

		bool empty()
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}

	private:
		Container _con;
	};

}

























































