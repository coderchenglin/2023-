#include <iostream>

using namespace std;

//IO流
//namespace

//stdlib.h库中,有一个名叫rand的函数,那么我们自己定义变量名就不能交rand

//namespace bit
//{
//		int a = 0;
//}
//
////如果不使用域作用限定符 :: ,即不指定命名空间,那么只会在全局区域找,不会去命名空间里面找
//
//int main()
//{
//		//int rand = 1;
////		std::cout << "hello world\n" << std::endl;
//		printf("rand = %d",  a);    //不会默认去到命名空间里面去找
//		// 流插入
//		//std::cout <<"rand = "<< bit::rand <<  &rand<< std::endl;
//
//		return 0;
//
//}
//
//// :: 这个符号左边是 空白 ,代表去全局域去找





//1.命名空间里面不仅可以定义变量,还可以定义类型

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


//命名空间展开

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



//缺省参数
//半缺省/ 部分缺省  --  只能由右往左连续缺省
// 
//void func(int a, int b = 10,int c = 20)  //可以
//void func(int a,int b = 10,int c)  //不可以   --   必须从右往左连续缺省,即不能b缺省c不缺省

//如果想做到如此,可以把b和c换个位置   把b放在最后就可以了

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




//函数重载:参数不同
//参数顺序不同,  参数个数不同,  参数类型不同


//函数重载和缺省参数结合
//语法上讲,下面的两个函数,构成函数重载
//但是在直接无参数调用的时候,会出现二义性(系统不知道我调用的是哪个)
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
//	f(10);        //f(int a, char b)   ->调用的是第二个
//	f(10, 20);  //f(int a ,char b)   ->调用的是第二个
//
//	//f();           //这个会报错 : 对重载函数的调用不明确  (存在歧义,不知道调用的是哪个)
//}

void swap(int& m, int& n)   //这里的m和n不是指针,而是引用,引用是原变量的别名
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

