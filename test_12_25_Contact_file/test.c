#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//struct S
//{
//	int n;
//	int arr[];//柔性数组成员
//};
//
//int main()
//{
//	int sz = sizeof(struct S);
//	printf("%d\n", sz);   //4
//	struct S s;
//
//	//柔性数组的使用
//	struct S* ps = (struct S*)malloc(sizeof(struct S) + 40);
//	if (ps == NULL)
//	{
//		perror("error");
//		return 1;
//	}
//
//	ps->n = 100;
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		ps->arr[i] = i;
//	}
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d", ps->arr[i]);
//	}
//
//
//	struct S* ptr = (struct S*)realloc(ps, sizeof(struct S) + 80);
//	if (ptr != NULL)
//	{
//		ps = ptr;
//		ptr = NULL;
//	}
//
//	//...
//	//释放
//	free(ps);
//	ps = NULL;
//
//	return 0;
//}



//FILE

#include<string.h>
#include<errno.h>

//int main()
//{
//	FILE* pf = fopen("test.txt", "w");
//	if (pf == NULL)
//	{
//		perror("error");
//		return 1;
//	}
//	//
//	//写文件
//
//	//关闭文件
//	fclose(pf);
//	pf = NULL;
//	return 0;
//}


////写一个字符
////执行结束后,文件test.txt文件中就有了26个字母
//int main()
//{
//	FILE* pf = fopen("test.txt", "w");
//	if (pf == NULL)
//	{
//		perror("error");
//		return 1;
//	}
//	for (int i = 'a'; i <= 'z'; i++)
//	{
//		fputc(i, pf);  //参数:要写的字符,文件指针
//	}
//	//关闭文件
//	fclose(pf);
//	pf = NULL;
//
//	return 0;
//}

//读字符
//int main()
//{
//	FILE* pf = fopen("test.txt", "r");
//	if (pf == NULL)
//	{
//		perror("errno");
//		return 1;
//	}
//
//	int ch[100] = { 0 };
//	for (int i = 0; i < 26; i++)
//	{
//		ch[i] = fgetc(pf);  //参数:文件指针
//	}
//	for (int i = 0; i < 26; i++)
//	{						 //文件里本来就有这26个字母
//		printf("%c", ch[i]); //abcdefghijklmnopqrstuvwxyz
//	}
//	return 0;
//}




////写一行数据
//int main()
//{
//	FILE* pf = fopen("test.txt", "w");
//	if (pf == NULL)
//	{
//		printf("%s\n", strerror(errno));
//		return 1;
//	}
//
//	//写一行数据
//	fputs("hello world1\n", pf);
//	fputs("hello world2\n", pf);
//
//	//关闭文件
//	fclose(pf);
//	pf = NULL;
//
//	return 0;
//}



//int main()
//{
//	FILE* pf = fopen("test.txt", "r");
//	if (pf == NULL)
//	{
//		perror("error");
//		return 1;
//	}
//
//	//读一行数据
//	char arr[20] = {0};
//	fgets(arr, 20, pf);  //读到哪里去,最多读多少,文件指针(从哪里读)
//
//	printf("%s\n", arr);//hello world1
//
//	//关闭文件
//	fclose(pf);
//	pf = NULL;
//
//	return 0;
//}



//struct S
//{
//	char arr[10];
//	int age;
//	float score;
//};




//从文件中以读
//int main()
//{
//	struct S s = {0};
//	FILE* pf = fopen("test.txt", "r");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//
//	fscanf(pf, "%s%d%f", s.arr, &(s.age), &(s.score));
//	fprintf(stdout,"%s %d %f\n", s.arr, s.age, s.score);
//
//	fclose(pf);
//	pf = NULL;
//
//	return 0;
//}



//
//int main()
//{
//	struct S s = { "zhangsan",25,50.5f };
//
//	FILE* pf = fopen("test.txt", "w");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//
//	fprintf(pf, "%s %d %f", s.arr, s.age, s.score);
//
//	fclose(pf);
//	pf = NULL;
//	return 0;
//
//}



//struct S
//{
//	char arr[10];
//	int age;
//	float score;
//};

//int main()
//{
//	struct S s = { 0 };
//	//以二进制的形式写到文件中
//	FILE* pf = fopen("test.txt", "rb");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//
//	//用二进制的方式读
//	fread(&s, sizeof(struct S), 1, pf);//读到哪里去,一次读取的元素大小,一次读取的元素个数,从哪里读
//	printf("%s %d %f\n", s.arr, s.age, s.score);
//
//	fclose(pf);
//	pf = NULL;
//	return 0;
//}

//int main()
//{
//	struct S s = { "zhangsan",25,50.5f };
//	//以二进制的形式写到文件中
//	FILE* pf = fopen("test.txt", "wb");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//
//	//以二进制的方式写
//	fwrite(&s, sizeof(struct S), 1, pf); //写的内容的地址,一次写入元素大小,一次写入元素个数,写到哪里去(文件指针)
//
//	fclose(pf);
//	pf = NULL;
//	return 0;
//
//}







//struct S
//{
//	char arr[10];
//	int age;
//	float score;
//};
//
//int main()
//{
//	struct S s = { "zhangsan",20,55.5f };
//	struct S tmp = { 0 };
//	char buf[100] = { 0 };
//	//把S中的格式化数据转化成字符串放到buf中
//	sprintf(buf, "%s %d %f", s.arr, s.age, s.score);
//
//	printf("字符串:%s\n", buf); //字符串:zhangsan 20 55.500000
//
//	//从字符串buf中获取一个格式化的数据存到tmp中
//	sscanf(buf, "%s %d %f", tmp.arr, &(tmp.age), &(tmp.score));
//	printf("格式化:%s %d %f\n", tmp.arr, tmp.age, tmp.score);//格式化:zhangsan 20 55.500000
//	return 0;
//
//}





//读字符

//fseek 的三个参数 SEEK_SET SEEK_END SEEK_CUR
//                   开始     末尾     当前 

//ftell 返回值为指针偏移量

//rewind 偏移量回到起始位置
int main()
{
	FILE* pf = fopen("test.txt", "r");
	if (pf == NULL)
	{
		printf("%s\n", strerror(errno));
		return 1;
	}

	//读文件  //假设文件中存放的是abcdef
	//定位文件指针
	fseek(pf, 2, SEEK_SET);
	int ch = fgetc(pf);
	printf("%c\n", ch); //c
	printf("%d\n", ftell(pf));//3

	//fseek(pf, 2, SEEK_CUR);
	fseek(pf, -1, SEEK_END);
	ch = fgetc(pf);
	printf("%c\n", ch); //f
	printf("%d\n", ftell(pf));//6

	rewind(pf);//文件指针回到起始位置
	ch = fgetc(pf);
	printf("%c\n", ch);//a

	//关闭文件
	fclose(pf);
	pf = NULL;

	return 0;
}

