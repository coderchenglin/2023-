


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

//��:˳��洢

typedef struct heap
{
	int* a;
	int size;
	int capacity;
}HP;

//��ʼ��
void init(HP* php)
{
	php->a = NULL;
	php->capacity = php->size = 0;
}

//����
void destroy(HP* php)
{
	free(php->a);
	php->capacity = php->size = 0;
	php = NULL;
}

//����
void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//��ӡ
void Print(HP* php)
{
	for (int i = 0; i < php->size; i++)
	{
		printf("%d ", php->a[i]);
	}
	printf("\n");
}

//���ϵ��� - ��С��
void AdjustUp(HP* php,int child)
{
	int parent = (child - 1) / 2;

	while (child > 0)
	{
		if (php->a[child] < php->a[parent])
		{
			Swap(&php->a[child], &php->a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

//����̬���ٵ����ݲ�������,Ҫ�ǵ�,��Ҫ������!
//���������,��һ����̬���ٵ����������,��Ҫдһ��'����'������,
//��������ط�ֻ�в�������һ��Ҫ�õ�����,����ֱ��д��ȥ��

//�ֵ�!��tm������malloc????
//�϶���realloc��,Ҫ��Ȼ��ô����ô��С��,��mallocÿ��һ�����¿�һ����?!

//�������� - ��С��
void Push(HP* php,int x)
{
	if (php->size == php->capacity)
	{
		int newcapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		int* tmp = (int*)realloc(php->a,sizeof(int) * newcapacity);
		if (tmp == NULL)
		{
			perror("malloc fail");
			exit(-1);
		}
		php->a = tmp;
		php->capacity = newcapacity;
	}

	php->a[php->size] = x;
	AdjustUp(php,php->size);
	php->size++;

}

//�п�
bool JudgeVoid(HP* php)
{
	return php->size == 0;
}

//���µ��� -- С��
//����������:
//int size���Կ������µ�����ʲôλ��(�����뵽���µ��������Ԫ�ص��±�+1) -- ��������Ҫ�������
//int parent���Կ������ĸ������µ���
//
//Ӧ��:
//1.ɾ���Ѷ�Ԫ��
//2.������  -- ��Ҫ�õ�int size�������
//3.����

//�¸���:���µ���,����Ҫ��һ���ѽ���ѽ!�Ǹ��������ѽ
void AdjustDown(int* a,int parent,int size) 
{
	int minchild = parent * 2 + 1;
	//ѡС�Ķ��ӽ���
	while (minchild<size)
	{
		if (minchild + 1 < size && a[minchild] > a[minchild + 1])
		{
			minchild++;
		}
		if (a[minchild] < a[parent])
		{
			Swap(&a[minchild], &a[parent]);
		}
		else
		{
			break;
		}

		parent = minchild;
		minchild = parent * 2 + 1;
	}

	
}


//ɾ���Ѷ�����
Pop(HP* php)
{
	assert(!JudgeVoid(php));
	Swap(&php->a[0], &php->a[php->size - 1]);
	AdjustDown(php->a, 0,php->size-1);
	php->size--;

}

//������ - ���� - ��С��

//�����:�������ô�һ���ѽ���ѽ!Ϊɶ��Ҫ�Ѳ�����,�Ǹ�����Ϳ�������ѽ!
//a������,size��Ԫ�ظ���
void HeapSort(int* a,int size)
{
	while (size > 0)  //ע������ط����ܵ���0,Ҫ��Ȼa[size-1]����a[-1],��Խ����
	{
		Swap(&a[0],&a[size-1]);
		AdjustDown(a, 0, size-1);
		size--;
	}
}


//����
//���ϵ������� - С��
//void UpCreatHeap(int* a,int size)
//{
//	for (int i = 0; i < size; i++)
//	{
//		Push(a, a[i]);
//	}
//
//}

//���µ������� - �����һ����Ҷ�ӽ�㿪ʼ,���µ������� - С��
void DownCreatHeap(int* a, int size)
{
	for (int i = (size - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, i, size);
	}

}


//topk���� - ��� - ��С��
void TOPK(int* a,int k,int n)
{
	//��һ��k��Ԫ�ش�С��С��
	DownCreatHeap(a, n);

	//�Ѻ����n-k��Ԫ��,�������β���,����ķŽ�ȥ����
	for (int i = k; i < n; i++)
	{
		if (a[i] > a[0])
		{
			Swap(&a[i], &a[0]);
			AdjustDown(a, 0, k);
		}
	}

}



int main()
{
	//HP hp;
	//init(&hp);
	//Push(&hp, 7);
	//Push(&hp, 6);
	//Push(&hp, 5);
	//Push(&hp, 4);
	//Push(&hp, 3);
	//Push(&hp, 2);
	//Push(&hp, 1);

	//Print(&hp);

	//Pop(&hp);
	//Print(&hp);

	//Pop(&hp);
	//Print(&hp);

	//Pop(&hp);
	//Print(&hp);

	////  1 4 2 7 5 6 3
	////	2 4 3 7 5 6
	////	3 4 6 7 5
	////	4 5 6 7
	//int a[] = { 1,2,3,4,5,6,7,8 };
	//HeapSort(a, sizeof(a) / sizeof(int));
	//for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	//{
	//	printf("%d ", a[i]);
	//}
	//printf("\n");
	////����:8 7 6 5 4 3 2 1

	int b[] = { 8,7,6,5,4,3,2,1 };
	//DownCreatHeap(b, 8);
	//for (int i = 0; i < sizeof(b) / sizeof(int); i++)
	//{
	//	printf("%d ", b[i]);
	//}
	//printf("\n");
	//bС��:1 4 2 5 8 3 6 7

	TOPK(b, 3, sizeof(b) / sizeof(int));
	for (int i = 0; i < sizeof(b) / sizeof(int); i++)
	{
		printf("%d ", b[i]);
	}
	printf("\n");
	//top3:6 8 7 1 2 3 4 5 
}


//int main()
//{
//	int a[] = { 23,324,45,32,32,81,92,67,18,90, };
//
//	//HeapSort(a, sizeof(a) / sizeof(int));  //����
//	//for (int i = 0; i < sizeof(a) / sizeof(int); i++)
//	//{
//	//	printf("%d ", a[i]);
//	//}
//
//	topk(a, sizeof(a) / sizeof(int), 4);
//	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
//	{
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//}





























