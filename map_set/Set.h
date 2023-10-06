#pragma once
#pragma once

#include "RBTree.h"

namespace bit
{
	template<class K>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename RBTree<K, K, SetKeyOfT>::const_iterator iterator;
		typedef typename RBTree<K, K, SetKeyOfT>::const_iterator const_iterator;

		iterator begin() const
		{
			return _t.begin();
		}

		iterator end() const
		{
			return _t.end();
		}

		// 20:21
		pair<iterator, bool> insert(const K& key)  //这个返回值,是一个const迭代器
		{                                 //下面这个iterator是用的RBTree的原生的iterator迭代器,而不是Set类中的,已经被定义成const类型的iterator迭代器
			pair<typename RBTree<K, K, SetKeyOfT>::iterator, bool> ret = _t.Insert(key); //RBTree的Insert函数的返回值是一个普通迭代器,这一步先接收
			           //下面这个iterator是定义为const类型的iterator                                 
			return pair<iterator, bool>(ret.first, ret.second); //这一步相当于用一个普通迭代器,构造一个const迭代器
		}
	private:
		RBTree<K, K, SetKeyOfT> _t;
	};

	void test_set()
	{
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		set<int> s;
		for (auto e : a)
		{
			s.insert(e);
		}

		set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			//*it += 10;
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : s)
		{
			cout << e << " ";
		} 
		cout << endl;
	}
}
