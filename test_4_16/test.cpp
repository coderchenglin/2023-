#include <iostream>

using namespace std;

//IO��
//namespace

//stdlib.h����,��һ������rand�ĺ���,��ô�����Լ�����������Ͳ��ܽ�rand

//namespace bit
//{
//		int a = 0;
//}
//
////�����ʹ���������޶��� :: ,����ָ�������ռ�,��ôֻ����ȫ��������,����ȥ�����ռ�������
//
//int main()
//{
//		//int rand = 1;
////		std::cout << "hello world\n" << std::endl;
//		printf("rand = %d",  a);    //����Ĭ��ȥ�������ռ�����ȥ��
//		// ������
//		//std::cout <<"rand = "<< bit::rand <<  &rand<< std::endl;
//
//		return 0;
//
//}
//
//// :: ������������ �հ� ,����ȥȫ����ȥ��





//1.�����ռ����治�����Զ������,�����Զ�������

//namespace bit
//{
//	int rand = 10;
//	int x = 1;
//
//	int Add(int left, int right)
//	{
//		return left + right;
//	}
//
//	struct Node
//	{
//		struct Node* next;
//		int val;
//	};
//
//}
//
//
//namespace N1
//{
//	int a = 0;
//	namespace N1
//	{
//		int b = 0;
//	}
//}
//
//int main()
//{
//	printf("%d\n", bit::Add(1, 2));
//	struct bit :: Node node;
//	N1::N1::b;
//
//	return 0;
//}


//�����ռ�չ��

//#include<iostream>
//using namespace std;
//using std::cout;
//
//int main()
//{
//	cout << "hello world" << endl;
//
//	return 0;
//}



//ȱʡ����
//��ȱʡ/ ����ȱʡ  --  ֻ��������������ȱʡ
// 
//void func(int a, int b = 10,int c = 20)  //����
//void func(int a,int b = 10,int c)  //������   --   ���������������ȱʡ,������bȱʡc��ȱʡ

//������������,���԰�b��c����λ��   ��b�������Ϳ�����

//void func(int a, int b = 10, int c = 20)
//{
//	cout << "a = " << a  << endl;
//	cout << "b = " << b << endl;
//	cout << "c = " << c  << endl;
//}
//
//int main()
//{
//	func(1);         //1 10 20
//	func(1, 2);     //1 2 20
//	func(1, 2, 3); //1 2 3
//
//	return 0;
//}




//��������:������ͬ
//����˳��ͬ,  ����������ͬ,  �������Ͳ�ͬ


//�������غ�ȱʡ�������
//�﷨�Ͻ�,�������������,���ɺ�������
//������ֱ���޲������õ�ʱ��,����ֶ�����(ϵͳ��֪���ҵ��õ����ĸ�)
//void f()
//{
//	cout << "f()" << endl;
//}
//
//void f(int a = 0, char b = 1)
//{
//	cout << "f(int a ,char b)" << endl;
//}
//
//int main()
//{
//	f(10);        //f(int a, char b)   ->���õ��ǵڶ���
//	f(10, 20);  //f(int a ,char b)   ->���õ��ǵڶ���
//
//	//f();           //����ᱨ�� : �����غ����ĵ��ò���ȷ  (��������,��֪�����õ����ĸ�)
//}

void swap(int& m, int& n)   //�����m��n����ָ��,��������,������ԭ�����ı���
{
	int tmp = m;
	m = n;
	n = tmp;
}

struct ListNode
{
	struct ListNode* next;
	int val;
};

void SlistPushBack(struct )

int  main()
{
	int a = 10;
	int& ra = a;
	int& x = a;
	int& y = x;

	x++;
	y++;
	a++;



	return 0;
}

