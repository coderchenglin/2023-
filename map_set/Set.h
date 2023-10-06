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
		pair<iterator, bool> insert(const K& key)  //�������ֵ,��һ��const������
		{                                 //�������iterator���õ�RBTree��ԭ����iterator������,������Set���е�,�Ѿ��������const���͵�iterator������
			pair<typename RBTree<K, K, SetKeyOfT>::iterator, bool> ret = _t.Insert(key); //RBTree��Insert�����ķ���ֵ��һ����ͨ������,��һ���Ƚ���
			           //�������iterator�Ƕ���Ϊconst���͵�iterator                                 
			return pair<iterator, bool>(ret.first, ret.second); //��һ���൱����һ����ͨ������,����һ��const������
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
