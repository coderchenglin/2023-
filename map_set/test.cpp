#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

//int main()
//{
//	std::set<int> myset;
//	std::set<int>::iterator itlow, itup;
//
//	for (int i = 1; i < 10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90
//
//	itlow = myset.lower_bound(35);    // >=            //       ^
//	itup = myset.upper_bound(75);     // >             //                   ^
//
//	myset.erase(itlow, itup);                     // 10 20 70 80 90
//
//	std::cout << "myset contains:";
//	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
//		std::cout << ' ' << *it;
//	std::cout << '\n';
//
//	return 0;
//}

//int main()
//{
//	map<string, string> dict;
//	dict.insert(pair<string, string>("����", "sort"));
//	dict.insert(pair<string, string>("���", "left"));
//	dict.insert(pair<string, string>("�ұ�", "right"));
//	dict.insert(make_pair("�ַ���", "string")); 
//	dict["������"] = "iterator"; // ����+�޸�
//	dict["insert"]; // ����  key���ھ��ǲ���
//	dict.insert(pair<string, string>("���", "xxx")); // ����ʧ�ܣ�������ֻ�Ƚ�key
//	dict["insert"] = "����"; //�޸�
//	cout << dict["���"] << endl; // ����  key�ھ��ǲ���
//
//	//map<string, string>::iterator it = dict.begin();
//	auto it = dict.begin();
//	while (it != dict.end())
//	{
//		//cout << (*it).first<<":"<<(*it).second << endl;
//		cout << it->first << ":" << it->second << endl;
//		++it;
//	}
//	cout << endl;
//
//	for (const auto& kv : dict)
//	{
//		cout << kv.first << ":" << kv.second << endl;
//	}
//
//	// ͳ��ˮ�����ֵĴ���
//	string arr[] = { "ƻ��", "����", "�㽶", "��ݮ", "ƻ��", "����", "ƻ��", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶" };
//
//	map<string, int> countMap;
//	//for (auto& e : arr)
//	//{
//	//	//map<string, int>::iterator it = countMap
//	//	auto it = countMap.find(e);
//	//	if (it == countMap.end())
//	//	{
//	//		countMap.insert(make_pair(e, 1));
//	//	}
//	//	else
//	//	{
//	//		it->second++;
//	//	}
//	//}
//
//	for (auto& e : arr)
//	{
//		countMap[e]++;
//	}
//
//	for (const auto& kv : countMap)
//	{
//		cout << kv.first << ":" << kv.second << endl;
//	}
//
//	return 0;
//}

//int main()
//{
//	multimap<string, string> dict;
//	dict.insert(make_pair("left", "���"));
//	dict.insert(make_pair("left", "ʣ��"));
//	dict.insert(make_pair("string", "�ַ���"));
//	dict.insert(make_pair("left", "xxx"));
//
//	for (const auto& kv : dict)
//	{
//		cout << kv.first << ":" << kv.second << endl;
//	}
//
//		string arr[] = { "ƻ��", "����", "�㽶", "��ݮ", "ƻ��", "����", "ƻ��", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶" };
//	
//		multimap<string, int> countMap;
//		for (auto& e : arr)
//		{
//			//map<string, int>::iterator it = countMap
//			auto it = countMap.find(e);
//			if (it == countMap.end())
//			{
//				countMap.insert(make_pair(e, 1));
//			}
//			else
//			{
//				it->second++;
//			}
//		}
//	
//		for (const auto& kv : countMap)
//		{
//			cout << kv.first << ":" << kv.second << endl;
//		}
//
//	return 0;
//}

//#include "AVLTree.h"
#include "RBTree.h"

#include "Map.h"
#include "Set.h"

#include <list>

int main()
{
	//TestAVLTree2();
	//TestRBTree1();

	bit::test_map();
	bit::test_set();

	//testRBTree();

	//list<int> lt;
	//list<int>::const_iterator it = lt.begin();

	//set<int> s;
	//set<int>::const_iterator sit = s.begin();

	//double d = 1.1;
	//int i = 0;
	//int* p = nullptr;
	//p = (int*)i;
	//p = (int*)d;

	return 0;
}