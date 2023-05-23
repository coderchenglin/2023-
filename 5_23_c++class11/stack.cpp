#include "stack.h"

//类模板的分析编译,和普通的有区别
//1.每一个函数前都得加上类模板
//2.不仅要指定类域,还要显示写上模板类型<T>


template<typename T>
Stack<T>::Stack(int capacity)            //类模板的成员的外部定义不得具有默认参数
{
	cout << "Stack(int capacity = )" << capacity << endl;

	_a = (T*)malloc(sizeof(T) * capacity);
	if (_a == nullptr)
	{
		perror("malloc fail");
		exit(-1);
	}

	_top = 0;
	_capacity = capacity;
}

template<class T>

Stack<T>::~Stack()
{
	cout << "~Stack()" << endl;

	free(_a);
	_a = nullptr;
	_top = _capacity = 0;
}

template<class T>
void Stack<T>::Push(const T& x)     //类模板  通常推荐使用  传引用传参,减少自定义类型的拷贝构造
{                                                                             //在不改变的情况下,推荐使用const引用
	//...
	//扩容
	_a[_top++] = x;
}


//如果就只有上面的代码,test.cpp中定义变量的时候,会出现编译错误

//解决方案:
// 1.显示实例化    --    原因,stack.cpp中不知道我在test.cpp定义的类型
template
class Stack<int>;

//但是,有个问题, Stack<double>,又要重新显示实例化

// 2.不分离定义,把声明和定义都放在 stack.h 文件中   































