#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//struct S
//{
//	int n;
//	int arr[];//���������Ա
//};
//
//int main()
//{
//	int sz = sizeof(struct S);
//	printf("%d\n", sz);   //4
//	struct S s;
//
//	//���������ʹ��
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
//	//�ͷ�
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
//	//д�ļ�
//
//	//�ر��ļ�
//	fclose(pf);
//	pf = NULL;
//	return 0;
//}


////дһ���ַ�
////ִ�н�����,�ļ�test.txt�ļ��о�����26����ĸ
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
//		fputc(i, pf);  //����:Ҫд���ַ�,�ļ�ָ��
//	}
//	//�ر��ļ�
//	fclose(pf);
//	pf = NULL;
//
//	return 0;
//}

//���ַ�
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
//		ch[i] = fgetc(pf);  //����:�ļ�ָ��
//	}
//	for (int i = 0; i < 26; i++)
//	{						 //�ļ��ﱾ��������26����ĸ
//		printf("%c", ch[i]); //abcdefghijklmnopqrstuvwxyz
//	}
//	return 0;
//}




////дһ������
//int main()
//{
//	FILE* pf = fopen("test.txt", "w");
//	if (pf == NULL)
//	{
//		printf("%s\n", strerror(errno));
//		return 1;
//	}
//
//	//дһ������
//	fputs("hello world1\n", pf);
//	fputs("hello world2\n", pf);
//
//	//�ر��ļ�
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
//	//��һ������
//	char arr[20] = {0};
//	fgets(arr, 20, pf);  //��������ȥ,��������,�ļ�ָ��(�������)
//
//	printf("%s\n", arr);//hello world1
//
//	//�ر��ļ�
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




//���ļ����Զ�
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
//	//�Զ����Ƶ���ʽд���ļ���
//	FILE* pf = fopen("test.txt", "rb");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//
//	//�ö����Ƶķ�ʽ��
//	fread(&s, sizeof(struct S), 1, pf);//��������ȥ,һ�ζ�ȡ��Ԫ�ش�С,һ�ζ�ȡ��Ԫ�ظ���,�������
//	printf("%s %d %f\n", s.arr, s.age, s.score);
//
//	fclose(pf);
//	pf = NULL;
//	return 0;
//}

//int main()
//{
//	struct S s = { "zhangsan",25,50.5f };
//	//�Զ����Ƶ���ʽд���ļ���
//	FILE* pf = fopen("test.txt", "wb");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//
//	//�Զ����Ƶķ�ʽд
//	fwrite(&s, sizeof(struct S), 1, pf); //д�����ݵĵ�ַ,һ��д��Ԫ�ش�С,һ��д��Ԫ�ظ���,д������ȥ(�ļ�ָ��)
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
//	//��S�еĸ�ʽ������ת�����ַ����ŵ�buf��
//	sprintf(buf, "%s %d %f", s.arr, s.age, s.score);
//
//	printf("�ַ���:%s\n", buf); //�ַ���:zhangsan 20 55.500000
//
//	//���ַ���buf�л�ȡһ����ʽ�������ݴ浽tmp��
//	sscanf(buf, "%s %d %f", tmp.arr, &(tmp.age), &(tmp.score));
//	printf("��ʽ��:%s %d %f\n", tmp.arr, tmp.age, tmp.score);//��ʽ��:zhangsan 20 55.500000
//	return 0;
//
//}





//���ַ�

//fseek ���������� SEEK_SET SEEK_END SEEK_CUR
//                   ��ʼ     ĩβ     ��ǰ 

//ftell ����ֵΪָ��ƫ����

//rewind ƫ�����ص���ʼλ��
int main()
{
	FILE* pf = fopen("test.txt", "r");
	if (pf == NULL)
	{
		printf("%s\n", strerror(errno));
		return 1;
	}

	//���ļ�  //�����ļ��д�ŵ���abcdef
	//��λ�ļ�ָ��
	fseek(pf, 2, SEEK_SET);
	int ch = fgetc(pf);
	printf("%c\n", ch); //c
	printf("%d\n", ftell(pf));//3

	//fseek(pf, 2, SEEK_CUR);
	fseek(pf, -1, SEEK_END);
	ch = fgetc(pf);
	printf("%c\n", ch); //f
	printf("%d\n", ftell(pf));//6

	rewind(pf);//�ļ�ָ��ص���ʼλ��
	ch = fgetc(pf);
	printf("%c\n", ch);//a

	//�ر��ļ�
	fclose(pf);
	pf = NULL;

	return 0;
}

