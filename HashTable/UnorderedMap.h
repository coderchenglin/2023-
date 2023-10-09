#pragma once
#include "HashTable.h"

namespace bit
{
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<const K, V>& kv)
			{
				return kv.first;
			}
		};

	public:

		typedef typename buckethash::HashTable<K, pair<const K, V>, Hash, MapKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		pair<iterator, bool> insert(const pair<K, V>& data)
		{
			return _ht.Insert(data);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		buckethash::HashTable<K, pair<const K, V>, Hash, MapKeyOfT> _ht;
	};

	void test_unordered_map()
	{
		string arr[] = { "ƻ", "", "㽶", "ݮ", "ƻ", "", "ƻ", "ƻ", "", "ƻ", "㽶", "ƻ", "㽶" };

		unordered_map<string, int> countMap;
		for (auto& e : arr)
		{
			countMap[e]++;
		}

		for (const auto& kv : countMap)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
	}
}
