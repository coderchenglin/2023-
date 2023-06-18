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


//˫�˶��� : ��֧��������� ��֧��ͷ��ͷɾ,β��βɾ
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
//	//���ȼ�����ԭ��:
//	/*template<
//		class T,
//		class Container = std::vector<T>,
//		class Compare = std::less<typename Container::value_type>  //less - ��� - ������ȼ���
//	> class priority_queue;*/                                      //greater - С�� - С�����ȼ���
//
//	//lp::priority_queue<int,vector<int>,greater<int>> pq;  // Ĭ���Ǵ�����ȼ��� - less
//														  // ���ҪС�����ȼ��� - greater
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

// ��ĳ���ڵ���жѻ�����
//void heapify(vector<int>& heap, int n, int i) {
//    int largest = i;    // ���赱ǰ�ڵ����
//    int left = 2 * i + 1;    // ���ӽڵ�����
//    int right = 2 * i + 2;    // �Һ��ӽڵ�����
//
//    // �Ƚ����ӽڵ�͸��ڵ��ֵ
//    if (left < n && heap[left] > heap[largest])
//        largest = left;
//
//    // �Ƚ��Һ��ӽڵ�͵�ǰ���ֵ
//    if (right < n && heap[right] > heap[largest])
//        largest = right;
//
//    // �����ǰ�ڵ㲻�����ֵ���򽻻��ڵ㲢�����ѻ�
//    if (largest != i) {
//        swap(heap[i], heap[largest]);
//        heapify(heap, n, largest);
//    }
//}
//
//// ��������
//void buildMaxHeap(vector<int>& heap) {
//    int n = heap.size();
//
//    // �����һ����Ҷ�ӽڵ㿪ʼ���жѻ�����
//    for (int i = n / 2 - 1; i >= 0; i--)
//        heapify(heap, n, i);
//}
//
//// ��ӡ��Ԫ��
//void printHeap(const vector<int>& heap) {
//    for (int i = 0; i < heap.size(); i++)
//        cout << heap[i] << " ";
//    cout << endl;
//}
//
//int main() {
//    vector<int> heap = { 4, 10, 3, 5, 1 };
//
//    cout << "��ʼ�ѣ�";
//    printHeap(heap);
//
//    buildMaxHeap(heap);
//
//    cout << "���ѣ�";
//    printHeap(heap);
//
//    return 0;
//}


//topk����:  �����
//1.�����  --  O(N + K*logN)     --   ���ʺ�N�ܴ�K��С����� -- �˷ѿռ�
//����һ��N�����Ĵ�� - O(N)
//��һ��pop K�� - O(K*logN)       !!!!!!!!!�ؼ�����!
//2.��С��  --  O(K + (N-K)*logK)
//����һ��k������С��  - O(K)
//����Ԫ�رȶѶ���,�ͽ��������,��������������,�Ѷ�Ԫ�ؾ��ǵ�K����� - (N-K)*logK


//topk����
//class Solution {
//public:
//    int findkthLargest(vector<int>& nums, int k) {
//        priority_queue<int> pq(nums.begin(), nums.end());  //���ȼ�����,֧���õ���������
//        while (--k)  //pop k-1 ��
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
//        priority_queue<int,vector<int>,greater<int>> pq(nums.begin(), nums.begin()+k);  //��С��
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



////�º���/��������
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
//	lp::less<int> lessFunc;  //lessFunc��һ����������
//	lp::greater<int> greaterFunc;  //lessFunc��һ����������
//
//	lessFunc(1, 2);
//	//�ȼ��� : lessFunc.operator()(1, 2);
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

	//ʹ���Զ���ķ������������
	cout << "�������: ";
	for (ReverseIterator<int> rit(&myList.back()); rit != ReverseIterator<int>(&myList.front()); ++rit)
	{
		cout << *rit << " ";
	}
	cout << endl;


	return 0;
}









