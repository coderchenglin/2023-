#pragma once
#pragma once

#include "RBTree.h"

namespace bit
{
	template<class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<const K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::const_iterator const_iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		const_iterator begin() const
		{
			return _t.begin();
		}

		const_iterator end() const
		{
			return _t.end();
		}

		pair<iterator, bool> insert(const pair<const K, V>& kv)
		{
			return _t.Insert(kv);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			return ret.first->second;
		}
	private:
		RBTree<K, pair<const K, V>, MapKeyOfT> _t;
	};

	void test_map()
	{
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		map<int, int> m;
		for (auto e : a)
		{
			m.insert(make_pair(e, e));
		}

		map<int, int>::iterator it = m.begin();
		while (it != m.end())
		{
			//it->first++;
			it->second++;
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;

		map<int, int>::const_iterator it2 = m.begin();
		while (it2 != m.end())
		{
			//it->first++;
			cout << it2->first << ":" << it2->second << endl;
			++it2;
		}
		cout << endl;

		map<string, int> countMap;
		string arr[] = { "ƻ", "", "㽶", "ݮ", "ƻ", "", "ƻ", "ƻ", "", "ƻ", "㽶", "ƻ", "㽶" };
		for (auto& e : arr)
		{
			countMap[e]++;
		}

		for (auto& kv : countMap)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
	}
}
