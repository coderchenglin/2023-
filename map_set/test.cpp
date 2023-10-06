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
//	dict.insert(pair<string, string>("排序", "sort"));
//	dict.insert(pair<string, string>("左边", "left"));
//	dict.insert(pair<string, string>("右边", "right"));
//	dict.insert(make_pair("字符串", "string")); 
//	dict["迭代器"] = "iterator"; // 插入+修改
//	dict["insert"]; // 插入  key不在就是插入
//	dict.insert(pair<string, string>("左边", "xxx")); // 插入失败，搜索树只比较key
//	dict["insert"] = "插入"; //修改
//	cout << dict["左边"] << endl; // 查找  key在就是查找
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
//	// 统计水果出现的次数
//	string arr[] = { "苹果", "西瓜", "香蕉", "草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
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
//	dict.insert(make_pair("left", "左边"));
//	dict.insert(make_pair("left", "剩余"));
//	dict.insert(make_pair("string", "字符串"));
//	dict.insert(make_pair("left", "xxx"));
//
//	for (const auto& kv : dict)
//	{
//		cout << kv.first << ":" << kv.second << endl;
//	}
//
//		string arr[] = { "苹果", "西瓜", "香蕉", "草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
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