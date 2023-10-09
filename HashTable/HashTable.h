#pragma once
#pragma once
#include<vector>
#include<iostream>
#include<string>
using namespace std;

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// 特化
template<>
struct HashFunc<string>
{
	// BKDR  -- 休息21：19
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

			// 大于标定负载因子，就需要扩容
			if (_n * 10 / _tables.size() >= 7)
			{
				// 旧表数据，重新计算，映射到新表
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
				// 线性探测
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
		size_t _n = 0;	// 表中存储的有效数据的个数
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
		string arr[] = { "苹果", "西瓜", "香蕉", "草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

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
	template<class T>
	struct HashNode
	{
		//pair<K, V> _kv;
		T _data;  //哈希桶里面存的数据的类型就是T
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};

//模板类参数的解释
	//  K：这是表示哈希表中的键（key）的类型。在哈希表中，键是用于查找值的关键信息。

	//	T：这是表示哈希表中存储的值（value）的类型。哈希表通常是一个键值对的数据结构，T 表示值的类型。

	//	Hash：这是表示用于计算哈希值的哈希函数的类型。哈希函数将键映射到哈希表中的存储位置。

	//	KeyOfT：这是一个函数对象（functor），用于从值类型 T 中提取键类型 K。在哈希表中，有时需要从值中提取键以进行查找和操作。

	// 前置声明
	template<class K, class T, class Hash, class KeyOfT>   
	class HashTable;

	// 为什么const迭代器没有复用?
	template<class K, class T, class Hash, class KeyOfT>
	struct __HTIterator
	{
		typedef HashNode<T> Node; //哈希节点
		typedef __HTIterator<K, T, Hash, KeyOfT> Self;//迭代器

		typedef HashTable<K, T, Hash, KeyOfT> HT; //哈希表

		Node* _node;
		HT* _ht;

		//构造
		__HTIterator(Node* node, HT* ht)
			:_node(node)
			, _ht(ht)
		{}

		//重载operator* 拿到节点的数据
		T& operator*()
		{
			return _node->_data;
		}

		//重载operator-> 拿到 节点的数据的地址 ,返回值是T*
		T* operator->()
		{
			return &_node->_data; //节点的数据的地址
		}

		bool operator != (const Self& s) const
		{
			return _node != s._node;
		}

		//前置++
		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				// 当前桶走完了，要找下一个桶的第一个
				KeyOfT kot;
				Hash hash;
				//找到当前数据的 哈希 下标
				size_t hashi = hash(kot(_node->_data)) % _ht->_tables.size();
				//从下一个开始找
				++hashi;
				while (hashi < _ht->_tables.size())
				{
					if (_ht->_tables[hashi])
					{
						_node = _ht->_tables[hashi];
						break;
					}
					else
					{
						++hashi;
					}
				}

				// 后面没有桶了
				if (hashi == _ht->_tables.size())
					_node = nullptr;
			}

			return *this;  //返回的是当前对象的  引用!!
		}
	};

	template<class K, class T, class Hash, class KeyOfT>
	class HashTable
	{
		typedef HashNode<T> Node; //节点

		template<class K, class T, class Hash, class KeyOfT>
		friend struct __HTIterator;    //友元类声明

	public:
		typedef __HTIterator<K, T, Hash, KeyOfT> iterator; //迭代器

		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					return iterator(_tables[i], this);
				}
			}

			return iterator(nullptr, this);
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		//初始化
		HashTable()
			:_n(0)
		{
			//_tables.resize(10);
			_tables.resize(__stl_next_prime(0));
		}

		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				// 释放桶
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;  //保存下一个节点
					delete cur;
					cur = next;
				}

				_tables[i] = nullptr;  //讲指针数组置空
			}
		}

		pair<iterator, bool> Insert(const T& data)  //直接传数据,类型为T
		{
			KeyOfT kot;

			//如果数据已经存在,那么插入失败,但是可以用来  "计数"
			iterator it = Find(kot(data));
			if (it != end())
				return make_pair(it, false);  //返回已存在数的迭代器

			// 负载因子控制在1，超过就扩容
			if (_tables.size() == _n)
			{
				/*HashTable<K, V, Hash> newHT;
				newHT._tables.resize(_tables.size() * 2);
				for (auto cur : _tables)
				{
				while (cur)
				{
				newHT.Insert(cur->_kv);
				cur = cur->_next;
				}
				}
				_tables.swap(newHT._tables);*/

				//定义一个新的哈希表 -- 一个指针数组
				vector<Node*> newTables;
				//newTables.resize(2 * _tables.size(), nullptr);
				newTables.resize(__stl_next_prime(_tables.size()), nullptr);  //扩容,用nullptr指针填充

				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					//若不为空,遍历该位置的单链表,利用里面的节点
					while (cur)
					{
						Node* next = cur->_next;

						size_t hashi = Hash()(kot(cur->_data)) % newTables.size();
						// 头插到新表
						cur->_next = newTables[hashi];
						newTables[hashi] = cur;

						cur = next;
					}

					_tables[i] = nullptr;  //遍历指针数组,全部置空
				}

				_tables.swap(newTables);
			}

			size_t hashi = Hash()(kot(data)) % _tables.size();
			// 头插
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];  //newnode的next指向_tables[hashi]中存的地址指向的对象
			                                  //就是说,_tables[hashi]就是这个哈希表指向的第一个节点(就是这个指针变量指向的节点)
			_tables[hashi] = newnode;
			++_n;

			return  make_pair(iterator(newnode, this), true);
		}

		iterator Find(const K& key) //传进值,直接找到哈希下标
		{
			KeyOfT kot;
			size_t hashi = Hash()(key) % _tables.size();   //这里是一个仿函数,是由用户传进来的仿函数
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return iterator(cur, this);
				}
				else
				{
					cur = cur->_next;
				}
			}
			//如果找到最后,也没有返回,说明整张表中没有要找的数据,返回 迭代器 的最后位置
			return end();
		}

		//删除
		bool Erase(const K& key)
		{
			size_t hashi = Hash()(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					// 准备删除
					if (cur == _tables[hashi])
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					--_n;

					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}

			return false;
		}

		inline unsigned long __stl_next_prime(unsigned long n)
		{
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};

			for (int i = 0; i < __stl_num_primes; ++i)
			{
				if (__stl_prime_list[i] > n)
				{
					return __stl_prime_list[i];
				}
			}

			return __stl_prime_list[__stl_num_primes - 1];
		}

	private:
		vector<Node*> _tables;  // 指针数组
		size_t _n = 0;  //实际存储数据量

		//vector<Data> _tables;
	};

	//struct Data
	//{
	//	list<>
	//	set<>
	//	size_t _size;
	//};
}



//总结:哈希表中,K是哈希表的键,T是哈希表的值,Hash是用来计算数据的hash值的,因为传进来的数据
//不一定是整数,我们要使用哈希表存数据,必须想办法将数据转成整形,然后KeyOfT是一个传入的函数,
//用来计算K中的T.
//K是哈希表的键,同时是unordered_map或者unordered_set的键值对K
//期中unordered_map的K是pair<K,V>,即K中的T是 "V" , unordered_set的K中的T还是"K"


//所以我们这是实现了一个通用的哈希表,上层的迭代器,由上层的容器传入的参数决定!