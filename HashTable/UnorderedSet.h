#pragma once
#include "HashTable.h"

namespace bit
{
	template<class K, class Hash = HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename buckethash::HashTable<K, K, Hash, SetKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}
	private:
		buckethash::HashTable<K, K, Hash, SetKeyOfT> _ht;
	};


	void test_unordered_set()
	{
		unordered_set<int> us;
		us.insert(13);
		us.insert(3);
		us.insert(23);
		us.insert(5);
		us.insert(5);
		us.insert(6);
		us.insert(15);
		us.insert(223342);
		us.insert(22);

		unordered_set<int>::iterator it = us.begin();
		while (it != us.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : us)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}