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
//	//swap(a, b);             //�����غ����ĵ��ò���ȷ  --   ��������  -- ��Ϊ��std��չ����,�Ϳ�������ͻ
//	lp::swap(a, b);            //���Կ��԰��Լ�д������ߺ���,�Ž��Լ��������ռ�
//	std::swap(a, b);          //ָ���ÿ����
//
//	return 0;
//}


//ģ�岻֧�ַ������
int  main()
{
	Stack<int> st;
	st.Push(1);
	st.Push(2);


	return 0;
}

//stl��ʼ

//����    --    windows��Ĭ����GBK  ,  linux��Ĭ����UTF-8
//int main()
//{
//	char arr1[] = "abcd";
//	char arr2[] = "apple";
//	char arr3[] = "����";     //   �����ַ�����һ������
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



//string   ---  ��̬�������ַ�����

//�򵥵ĵײ�ʵ��:
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
	string s1;       //���ַ���
	cout << s1 << endl;

	string s2("����ʡ�人��");    //��ʼ��һ���ַ���
	cout << s2 << endl;

	s2 += "�����";             // ���������
	cout << s2 << endl;

	//string s3 = "����ʡ�人��"��
	//cout << s3 << endl;

	string s4(10, '*');     //   ��ʼ����10��char�ַ�
	cout << s4 << endl;

	string s5(s2);        //��������
	string s6 = s2;      //��������
	cout << s5 << endl;
	cout << s6 << endl;

	//���� , ���ַ���,��һ��  �����ַ�������, �Լ���������,���ֹ���������Ҫ��

	string s7("hello world", 7);    //��"hello world"����ַ�����ǰ7���ַ�  ,  ������s7
	cout << s7 << endl;           //hello w

	string s8("hello world", 2, 7);        //�ӵ�2��λ��,��7���ַ�  ������s8      //ע��! �����7���ַ�̫�����ߵ���ͷ,��ô��ֱ�ӵ�string��ĩβ,���ᱨ��
	cout << s8 << endl;           //llo wor

	string s9(s7, 2, 3);                         //�ӵ�2��λ��,��3���ַ�   ������s9
	cout << s9 << endl;           //llo

	string s10(s7, 2);                         //   �����ȱʡֵ,����������������,��ôֱ�Ӵӵڶ�����ʼ,һֱ��stringĩβ
	cout << s10 << endl;           //llo w

}

//operator[]  ������ -- ���ص�������  -- ֻҪԽ��ͻᱨ��
// 
//char& operator[](size_t i)
//{
//	return _str[i];
//}

void test_string2()
{
	//дһ��С����demo:ʵ��������ַ���,ÿ���ַ���+1
	string s1("1234");

	//��������3�ַ�ʽ:
	//  1.  �±�ӷ�����   operator[]
	for (size_t i = 0; i < s1.size(); ++i)
	{
		s1[i]++;   // ������,ֻҪԽ��ͻᱨ��
	}
	cout << s1 << endl;   // 2345

	//  2. ��Χfor
	for (auto& ch : s1)          //����ȡs1���ַ�,��ֵ��ch,  ����Ҫ������&,���ܸı�s1��ֵ
	{
		ch--;
	}
	cout << s1 << endl;

	//��תһ��
	size_t begin = 0, end = s1.size() - 1;
	while (begin < end)
	{
		swap(s1[begin++], s1[end--]);
	}
	cout << s1 << endl;

	//������
	reverse(s1.begin(), s1.end());
	cout << s1 << endl;
}

int main()
{
	test_string1();

	test_string2();

	return 0;
}









