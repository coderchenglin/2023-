#pragma once
#pragma once
#include<vector>
#include<string>

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// �ػ�
template<>
struct HashFunc<string>
{
	// BKDR  -- ��Ϣ21��19
	size_t operator()(const string& key)
	{
		size_t hash = 0;
		for (auto ch : key)
		{
			hash *= 131;
			hash += ch;
		}
		return hash;
	}
};

namespace closehash
{

	enum State
	{
		EMPTY,
		EXIST,
		DELETE,
	};

	//struct HashFuncString
	//{
	//	size_t operator()(const string& key)
	//	{
	//		size_t hash = 0;
	//		for (auto ch : key)
	//		{
	//			hash += ch;
	//		}
	//		return hash;
	//	}
	//};

	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		State _state = EMPTY;
	};

	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashData<K, V> Data;
	public:
		HashTable()
			:_n(0)
		{
			_tables.resize(10);
		}

		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;

			// ���ڱ궨�������ӣ�����Ҫ����
			if (_n * 10 / _tables.size() >= 7)
			{
				// �ɱ����ݣ����¼��㣬ӳ�䵽�±�
				/*vector<Data> newTable;
				newTable.resize(_tables.size() * 2);
				for ()
				{
				}*/
				HashTable<K, V, Hash> newHT;
				newHT._tables.resize(_tables.size() * 2);
				for (auto& e : _tables)
				{
					if (e._state == EXIST)
					{
						newHT.Insert(e._kv);
					}
				}

				_tables.swap(newHT._tables);
			}

			Hash hf;
			size_t hashi = hf(kv.first) % _tables.size();
			while (_tables[hashi]._state == EXIST)
			{
				// ����̽��
				++hashi;
				hashi %= _tables.size();
			}

			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			++_n;

			return true;
		}

		Data* Find(const K& key)
		{
			Hash hf;
			size_t hashi = hf(key) % _tables.size();
			while (_tables[hashi]._state != EMPTY)
			{
				if (_tables[hashi]._state == EXIST
					&& _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi];
				}

				++hashi;
				hashi %= _tables.size();
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			Data* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				--_n;
				return true;
			}
			else
			{
				return false;
			}
		}
	private:
		vector<Data> _tables;
		size_t _n = 0;	// ���д洢����Ч���ݵĸ���
	};

	void TestHT1()
	{
		HashTable<int, int> ht;
		int a[] = { 18, 8, 7, 27, 57, 3, 38, 18 };
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		ht.Insert(make_pair(17, 17));
		ht.Insert(make_pair(5, 5));

		cout << ht.Find(7) << endl;
		cout << ht.Find(8) << endl;

		ht.Erase(7);
		cout << ht.Find(7) << endl;
		cout << ht.Find(8) << endl;
	}

	void TestHT2()
	{
		string arr[] = { "ƻ��", "����", "�㽶", "��ݮ", "ƻ��", "����", "ƻ��", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶" };

		//HashTable<string, int, HashFuncString> countHT;
		HashTable<string, int> countHT;
		for (auto& e : arr)
		{
			HashData<string, int>* ret = countHT.Find(e);
			if (ret)
			{
				ret->_kv.second++;
			}
			else
			{
				countHT.Insert(make_pair(e, 1));
			}
		}

		HashFunc<string> hf;
		cout << hf("abc") << endl;
		cout << hf("bac") << endl;
		cout << hf("cba") << endl;
		cout << hf("aad") << endl;
	}
}

namespace buckethash
{
	template<class K, class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;
	};

	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;

			// �������ӿ�����1������������
			if (_tables.size() == _n)
			{
				//
			}

			size_t hashi = Hash()(kv.first) % _tables.size();
			// ͷ��
			Node* newnode = new Node(kv);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;

			return true;
		}

	private:
		vector<Node*> _tables;
		size_t _n = 0;
	};
}