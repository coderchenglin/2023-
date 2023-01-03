

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef struct heap
{
	int* a;
	int size;
	int capacity;
}HP;

//��ʼ��
void init(HP* php)
{
	assert(php);
	php->a = NULL;
	php->capacity = php->size = 0;
}

//����
void destroy(HP* php)
{
	assert(php);
	free(php->a);
	php->capacity = php->size = 0;
}

//����
void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//��ӡ
void print(HP* php)
{
	assert(php);
	for (int i = 0; i < php->size; i++)
	{
		printf("%d ", php->a[i]);
	}
}


//���ϵ���
void AdjustUp(HP* php, int child)
{
	assert(php);
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (php->a[child] < php->a[parent])
		{
			swap(&php->a[child], &php->a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

//��������
void push(HP* php,int x)
{
	assert(php);
	if (php->size == php->capacity)
	{
		int newcapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		int* tmp = (int*)realloc(php->a, newcapacity * sizeof(int));
		if (tmp == NULL)
		{
			perror("realloc fail");
			exit(-1);
		}
		
		php->a = tmp;
		php->capacity = newcapacity;
	}
	php->a[php->size] = x;

	AdjustUp(php, php->size);
	php->size++;
}

//�п�
bool EmptyJudge(HP* php)
{
	assert(php);
	return php->size == 0;
}

//���µ��� - С��
void AdjustDown(int* a,int n,int parent)
{
	assert(a);

	int minchild = parent * 2 + 1;
	while (minchild < n)
	{
		if (minchild + 1 < n && a[minchild] > a[minchild + 1])
		{
			minchild++;
		}
		
		if (a[minchild] < a[parent])
		{
			swap(&a[minchild], &a[parent]);
			parent = minchild;
			minchild = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}

}

//ɾ���Ѷ�����
void pop(HP* php)
{
	assert(php);
	assert(!EmptyJudge(php));

	swap(&php->a[0], &php->a[php->size - 1]);
	AdjustDown(php->a, php->size-1,0);
	php->size--;

}


//������:����:�����  ����:��С��
//ѡ��ԭ��:ÿ�ν����Ļ������,�����µ���
//���ϵ�������:ʱ�临�Ӷ�:O(n*logn)
//���µ�������:ʱ�临�Ӷ�:O(n)

//������ - ���� - �����
void HeapSort(int* a,int n)
{
	//1.���� - ���µ�������
	//���һ��Ҷ�ӽ��ĸ����������һ����Ҷ�ӽ��
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}

	//2.ѡ�� - ÿ��ѡ��δ�������ں���
	int i = 1;
	while (i<n)
	{
		swap(&a[0], &a[n - i]);
		AdjustDown(a, n - i, 0);
		i++;
	}

}

//topK����
//ѡ��� - ��С��
//�����:�ռ临�Ӷ�ΪO(N),�����10�ڸ���ѡ100��,�޷����ڴ������
//��С��:�ռ临�Ӷ�ΪO(K)

//��С��˼·:�Ƚ�һ��k������С��,�ٰѺ�n-k����,���κͶѶ��������бȽ�,�ȶѶ���,�ͽ���,Ȼ��������µ���
void topk(int* a, int n,int k)
{
	//1.��С��
	for (int i = (k - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a, k, i);
	}

	//2.ȡ��������,���µ���
	for (int i = k; i < n; i++)
	{
		if (a[i] > a[0])
		{
			//swap(&a[i], &a[0]);  //��ط����ý���,��ֵ����
			a[0] = a[i];
			AdjustDown(a, k, 0);
		}
	}
}

//int main()
//{
//	HP php;
//	init(&php);
//	push(&php, 13);
//	push(&php, 12);
//	push(&php, 14);
//	push(&php, 6);
//
//	pop(&php);
//	pop(&php);
//	pop(&php);
//	pop(&php);
//
//	print(&php);
//
//	return 0;
//}

int main()
{
	int a[] = { 23,324,45,32,32,81,92,67,18,90,};

	//HeapSort(a, sizeof(a) / sizeof(int));  //����
	//for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	//{
	//	printf("%d ", a[i]);
	//}

	topk(a, sizeof(a) / sizeof(int), 4);
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}






















