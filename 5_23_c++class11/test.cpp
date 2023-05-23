#include"stack.h"


//namespace lp
//{
//	template<typename T>
//	void swap(T& left, T& right)
//	{
//		T temp = left;
//		left = right;
//		right = temp;
//	}
//}
//
//
//int main()
//{
//	int a = 0, b = 1;
//	//swap(a, b);             //对重载函数的调用不明确  --   库里面有  -- 因为把std给展开了,和库里面会冲突
//	lp::swap(a, b);            //所以可以把自己写的类或者函数,放进自己的命名空间
//	std::swap(a, b);          //指定用库里的
//
//	return 0;
//}


//模板不支持分离编译
int  main()
{
	Stack<int> st;
	st.Push(1);
	st.Push(2);


	return 0;
}

//stl开始

//编码    --    windows上默认是GBK  ,  linux上默认是UTF-8
//int main()
//{
//	char arr1[] = "abcd";
//	char arr2[] = "apple";
//	char arr3[] = "加油";     //   两个字符决定一个汉字
//
//	arr3[3]--;
//	arr3[3]--;
//	arr3[3]++;
//	arr3[3]++;
//	arr3[3]++;
//	arr3[3]++;
//
//	return 0;
//}



//string   ---  动态增长的字符数组

//简单的底层实现:
//template<class T>
//class basic_string
//{
//private:
//	T* _str;
//	size_t _size;
//	size_t _capacity;
//};
//
//typedef basic_string<char> string;



#include <string>

void test_string1()
{
	string s1;       //空字符串
	cout << s1 << endl;

	string s2("湖北省武汉市");    //初始化一个字符串
	cout << s2 << endl;

	s2 += "武昌区";             // 运算符重载
	cout << s2 << endl;

	//string s3 = "湖北省武汉市"；
	//cout << s3 << endl;

	string s4(10, '*');     //   初始化：10个char字符
	cout << s4 << endl;

	string s5(s2);        //拷贝构造
	string s6 = s2;      //拷贝构造
	cout << s5 << endl;
	cout << s6 << endl;

	//以上 , 空字符串,用一个  常量字符串构造, 以及拷贝构造,三种构造是最重要的

	string s7("hello world", 7);    //用"hello world"这个字符串的前7个字符  ,  来构造s7
	cout << s7 << endl;           //hello w

	string s8("hello world", 2, 7);        //从第2个位置,走7个字符  来构造s8      //注意! 如果走7个字符太长了走到了头,那么就直接到string的末尾,不会报错
	cout << s8 << endl;           //llo wor

	string s9(s7, 2, 3);                         //从第2个位置,走3个字符   来构造s9
	cout << s9 << endl;           //llo

	string s10(s7, 2);                         //   如果给缺省值,即第三个参数不给,那么直接从第二个开始,一直到string末尾
	cout << s10 << endl;           //llo w

}

//operator[]  方括号 -- 返回的是引用  -- 只要越界就会报错
// 
//char& operator[](size_t i)
//{
//	return _str[i];
//}

void test_string2()
{
	//写一个小功能demo:实现让这个字符串,每个字符都+1
	string s1("1234");

	//遍历他的3种方式:
	//  1.  下标加方括号   operator[]
	for (size_t i = 0; i < s1.size(); ++i)
	{
		s1[i]++;   // 方括号,只要越界就会报错
	}
	cout << s1 << endl;   // 2345

	//  2. 范围for
	for (auto& ch : s1)          //依次取s1的字符,赋值给ch,  所以要用引用&,才能改变s1的值
	{
		ch--;
	}
	cout << s1 << endl;

	//翻转一下
	size_t begin = 0, end = s1.size() - 1;
	while (begin < end)
	{
		swap(s1[begin++], s1[end--]);
	}
	cout << s1 << endl;

	//迭代器
	reverse(s1.begin(), s1.end());
	cout << s1 << endl;
}

int main()
{
	test_string1();

	test_string2();

	return 0;
}









