#include<iostream>
using namespace std;

//#include"stack.h"
//#include"queue.h"
#include"priority_queue.h"
#include"reverse_iterator.h"

#include<list>
#include<deque>
#include<queue>

#include<functional>

//int main()
//{
//	//lp::stack<int, vector<int>> st;
//	//lp::stack<int, list<int>> st;
//	//st.push(1);
//	//st.push(2);
//	//st.push(3);
//	//while(!st.empty())
//	//{
//	//	cout << st.top() << endl;
//	//	st.pop();
//	//}
//	//cout << endl;
//
//	lp::queue<int, list<int>> q;
//	q.push(1);
//	q.push(2);
//	q.push(3);
//	while (!q.empty())
//	{
//		cout << q.front() << endl;
//		q.pop();
//	}
//	cout << endl;
//
//	return 0;
//}


//双端队列 : 即支持随机访问 还支持头插头删,尾插尾删
//int main()
//{
//	deque<int> d;
//	d.push_back(1);
//	d.push_back(2);
//	d.push_back(3);
//	d.push_back(4);
//
//	d.push_front(10);
//	d.push_front(20);
//
//	for (size_t i = 0; i < d.size(); ++i)
//	{
//		cout << d[i] << " ";
//	}
//	cout << endl;
//
//	return 0;
//}


//int main()
//{
//	//优先级队列原型:
//	/*template<
//		class T,
//		class Container = std::vector<T>,
//		class Compare = std::less<typename Container::value_type>  //less - 大堆 - 大的优先级高
//	> class priority_queue;*/                                      //greater - 小堆 - 小的优先级高
//
//	//lp::priority_queue<int,vector<int>,greater<int>> pq;  // 默认是大的优先级高 - less
//														  // 如果要小的优先级高 - greater
//	lp::priority_queue<int> pq;  
//
//	pq.push(3);                                       
//	pq.push(1);
//	pq.push(2);
//	pq.push(5);
//
//	while (!pq.empty())
//	{
//		cout << pq.top() << " ";
//		pq.pop();
//	}
//
//	return 0;
//}

//#include <iostream>
//#include <vector>
//
//using namespace std;

// 对某个节点进行堆化操作
//void heapify(vector<int>& heap, int n, int i) {
//    int largest = i;    // 假设当前节点最大
//    int left = 2 * i + 1;    // 左孩子节点索引
//    int right = 2 * i + 2;    // 右孩子节点索引
//
//    // 比较左孩子节点和根节点的值
//    if (left < n && heap[left] > heap[largest])
//        largest = left;
//
//    // 比较右孩子节点和当前最大值
//    if (right < n && heap[right] > heap[largest])
//        largest = right;
//
//    // 如果当前节点不是最大值，则交换节点并继续堆化
//    if (largest != i) {
//        swap(heap[i], heap[largest]);
//        heapify(heap, n, largest);
//    }
//}
//
//// 建立最大堆
//void buildMaxHeap(vector<int>& heap) {
//    int n = heap.size();
//
//    // 从最后一个非叶子节点开始进行堆化操作
//    for (int i = n / 2 - 1; i >= 0; i--)
//        heapify(heap, n, i);
//}
//
//// 打印堆元素
//void printHeap(const vector<int>& heap) {
//    for (int i = 0; i < heap.size(); i++)
//        cout << heap[i] << " ";
//    cout << endl;
//}
//
//int main() {
//    vector<int> heap = { 4, 10, 3, 5, 1 };
//
//    cout << "初始堆：";
//    printHeap(heap);
//
//    buildMaxHeap(heap);
//
//    cout << "最大堆：";
//    printHeap(heap);
//
//    return 0;
//}


//topk问题:  找最大
//1.建大堆  --  O(N + K*logN)     --   不适合N很大K很小的情况 -- 浪费空间
//建立一个N个数的大堆 - O(N)
//再一次pop K次 - O(K*logN)       !!!!!!!!!关键步骤!
//2.建小堆  --  O(K + (N-K)*logK)
//建立一个k个数的小堆  - O(K)
//后面元素比堆顶大,就交换后沉底,遍历完整课树后,堆顶元素就是第K大的数 - (N-K)*logK


//topk问题
//class Solution {
//public:
//    int findkthLargest(vector<int>& nums, int k) {
//        priority_queue<int> pq(nums.begin(), nums.end());  //优先级队列,支持用迭代器建堆
//        while (--k)  //pop k-1 次
//        {
//            pq.pop();
//        }
//        return pq.top();
//    }
//};
//
//
//class Solution {
//public:
//    int findkthLargest(vector<int>& nums, int k) {
//        priority_queue<int,vector<int>,greater<int>> pq(nums.begin(), nums.begin()+k);  //建小堆
//        for (size_t i = k; i < nums.size(); i++)
//        {
//            if (nums[i] > pq.top())
//            {
//                pq.pop();
//                pq.push(nums[i]);
//            }
//        }
//
//        return pq.top();
//    }
//};



////仿函数/函数对象
//namespace lp
//{
//	template<class T>
//	class less
//	{
//	public:
//		bool operator()(const T& x, const T& y) const
//		{
//			return x < y;
//		}
//	};
//
//	template<class T>
//	class greater
//	{
//	public:
//		bool operator()(const T& x, const T& y) const
//		{
//			return x > y;
//		}
//	};
//}
//
//template<class T,class Compare>
//void BubbleSort(T* a, int n,const Compare com)
//{
//	for (int j = 0; j < n; ++j)
//	{
//		int exchange = 0;
//		for (int i = 1; i < n - j; ++i)
//		{
//			if (com(a[i], a[i - 1]))
//			{
//				swap(a[i - 1], a[i]);
//				exchange = 1;
//			}
//		}
//
//		if (exchange == 0)
//		{
//			break;
//		}
//	}
//}
//
//
//int main()
//{
//	lp::less<int> lessFunc;  //lessFunc是一个函数对象
//	lp::greater<int> greaterFunc;  //lessFunc是一个函数对象
//
//	lessFunc(1, 2);
//	//等价于 : lessFunc.operator()(1, 2);
//
//	int a[] = { 2, 3, 4, 5, 6, 1, 2, 4, 9 };
//
//	//BubbleSort(a, sizeof(a) / sizeof(int), lessFunc);
//	//BubbleSort(a, sizeof(a) / sizeof(int), lp::less<int>());
//
//	BubbleSort(a, sizeof(a) / sizeof(int), greaterFunc);
//
//	for (auto e : a)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	return 0;
//}


//struct PDateLess
//{
//	bool operator()(const Date* d1, const Date* d2)
//	{
//		return *d1 < *d2;
//	}
//};
//
//
//struct PDateLess
//{
//	bool operator()(const Date* d1, const Date* d2)
//	{
//		return *d1 > *d2;
//	}
//};



int main()
{
	list<int> myList = { 1,2,3,4,5 };

	//使用自定义的反向迭代器遍历
	cout << "反向遍历: ";
	for (ReverseIterator<int> rit(&myList.back()); rit != ReverseIterator<int>(&myList.front()); ++rit)
	{
		cout << *rit << " ";
	}
	cout << endl;


	return 0;
}









