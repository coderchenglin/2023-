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
	template<class T>
	struct HashNode
	{
		//pair<K, V> _kv;
		T _data;  //��ϣͰ���������ݵ����;���T
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};

//ģ��������Ľ���
	//  K�����Ǳ�ʾ��ϣ���еļ���key�������͡��ڹ�ϣ���У��������ڲ���ֵ�Ĺؼ���Ϣ��

	//	T�����Ǳ�ʾ��ϣ���д洢��ֵ��value�������͡���ϣ��ͨ����һ����ֵ�Ե����ݽṹ��T ��ʾֵ�����͡�

	//	Hash�����Ǳ�ʾ���ڼ����ϣֵ�Ĺ�ϣ���������͡���ϣ��������ӳ�䵽��ϣ���еĴ洢λ�á�

	//	KeyOfT������һ����������functor�������ڴ�ֵ���� T ����ȡ������ K���ڹ�ϣ���У���ʱ��Ҫ��ֵ����ȡ���Խ��в��ҺͲ�����

	// ǰ������
	template<class K, class T, class Hash, class KeyOfT>   
	class HashTable;

	// Ϊʲôconst������û�и���?
	template<class K, class T, class Hash, class KeyOfT>
	struct __HTIterator
	{
		typedef HashNode<T> Node; //��ϣ�ڵ�
		typedef __HTIterator<K, T, Hash, KeyOfT> Self;//������

		typedef HashTable<K, T, Hash, KeyOfT> HT; //��ϣ��

		Node* _node;
		HT* _ht;

		//����
		__HTIterator(Node* node, HT* ht)
			:_node(node)
			, _ht(ht)
		{}

		//����operator* �õ��ڵ������
		T& operator*()
		{
			return _node->_data;
		}

		//����operator-> �õ� �ڵ�����ݵĵ�ַ ,����ֵ��T*
		T* operator->()
		{
			return &_node->_data; //�ڵ�����ݵĵ�ַ
		}

		bool operator != (const Self& s) const
		{
			return _node != s._node;
		}

		//ǰ��++
		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				// ��ǰͰ�����ˣ�Ҫ����һ��Ͱ�ĵ�һ��
				KeyOfT kot;
				Hash hash;
				//�ҵ���ǰ���ݵ� ��ϣ �±�
				size_t hashi = hash(kot(_node->_data)) % _ht->_tables.size();
				//����һ����ʼ��
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

				// ����û��Ͱ��
				if (hashi == _ht->_tables.size())
					_node = nullptr;
			}

			return *this;  //���ص��ǵ�ǰ�����  ����!!
		}
	};

	template<class K, class T, class Hash, class KeyOfT>
	class HashTable
	{
		typedef HashNode<T> Node; //�ڵ�

		template<class K, class T, class Hash, class KeyOfT>
		friend struct __HTIterator;    //��Ԫ������

	public:
		typedef __HTIterator<K, T, Hash, KeyOfT> iterator; //������

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

		//��ʼ��
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
				// �ͷ�Ͱ
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;  //������һ���ڵ�
					delete cur;
					cur = next;
				}

				_tables[i] = nullptr;  //��ָ�������ÿ�
			}
		}

		pair<iterator, bool> Insert(const T& data)  //ֱ�Ӵ�����,����ΪT
		{
			KeyOfT kot;

			//��������Ѿ�����,��ô����ʧ��,���ǿ�������  "����"
			iterator it = Find(kot(data));
			if (it != end())
				return make_pair(it, false);  //�����Ѵ������ĵ�����

			// �������ӿ�����1������������
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

				//����һ���µĹ�ϣ�� -- һ��ָ������
				vector<Node*> newTables;
				//newTables.resize(2 * _tables.size(), nullptr);
				newTables.resize(__stl_next_prime(_tables.size()), nullptr);  //����,��nullptrָ�����

				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					//����Ϊ��,������λ�õĵ�����,��������Ľڵ�
					while (cur)
					{
						Node* next = cur->_next;

						size_t hashi = Hash()(kot(cur->_data)) % newTables.size();
						// ͷ�嵽�±�
						cur->_next = newTables[hashi];
						newTables[hashi] = cur;

						cur = next;
					}

					_tables[i] = nullptr;  //����ָ������,ȫ���ÿ�
				}

				_tables.swap(newTables);
			}

			size_t hashi = Hash()(kot(data)) % _tables.size();
			// ͷ��
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];  //newnode��nextָ��_tables[hashi]�д�ĵ�ַָ��Ķ���
			                                  //����˵,_tables[hashi]���������ϣ��ָ��ĵ�һ���ڵ�(�������ָ�����ָ��Ľڵ�)
			_tables[hashi] = newnode;
			++_n;

			return  make_pair(iterator(newnode, this), true);
		}

		iterator Find(const K& key) //����ֵ,ֱ���ҵ���ϣ�±�
		{
			KeyOfT kot;
			size_t hashi = Hash()(key) % _tables.size();   //������һ���º���,�����û��������ķº���
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
			//����ҵ����,Ҳû�з���,˵�����ű���û��Ҫ�ҵ�����,���� ������ �����λ��
			return end();
		}

		//ɾ��
		bool Erase(const K& key)
		{
			size_t hashi = Hash()(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					// ׼��ɾ��
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
		vector<Node*> _tables;  // ָ������
		size_t _n = 0;  //ʵ�ʴ洢������

		//vector<Data> _tables;
	};

	//struct Data
	//{
	//	list<>
	//	set<>
	//	size_t _size;
	//};
}



//�ܽ�:��ϣ����,K�ǹ�ϣ��ļ�,T�ǹ�ϣ���ֵ,Hash�������������ݵ�hashֵ��,��Ϊ������������
//��һ��������,����Ҫʹ�ù�ϣ�������,������취������ת������,Ȼ��KeyOfT��һ������ĺ���,
//��������K�е�T.
//K�ǹ�ϣ��ļ�,ͬʱ��unordered_map����unordered_set�ļ�ֵ��K
//����unordered_map��K��pair<K,V>,��K�е�T�� "V" , unordered_set��K�е�T����"K"


//������������ʵ����һ��ͨ�õĹ�ϣ��,�ϲ�ĵ�����,���ϲ����������Ĳ�������!