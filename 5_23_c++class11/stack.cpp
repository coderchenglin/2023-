#include "stack.h"

//��ģ��ķ�������,����ͨ��������
//1.ÿһ������ǰ���ü�����ģ��
//2.����Ҫָ������,��Ҫ��ʾд��ģ������<T>


template<typename T>
Stack<T>::Stack(int capacity)            //��ģ��ĳ�Ա���ⲿ���岻�þ���Ĭ�ϲ���
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
void Stack<T>::Push(const T& x)     //��ģ��  ͨ���Ƽ�ʹ��  �����ô���,�����Զ������͵Ŀ�������
{                                                                             //�ڲ��ı�������,�Ƽ�ʹ��const����
	//...
	//����
	_a[_top++] = x;
}


//�����ֻ������Ĵ���,test.cpp�ж��������ʱ��,����ֱ������

//�������:
// 1.��ʾʵ����    --    ԭ��,stack.cpp�в�֪������test.cpp���������
template
class Stack<int>;

//����,�и�����, Stack<double>,��Ҫ������ʾʵ����

// 2.�����붨��,�������Ͷ��嶼���� stack.h �ļ���   































