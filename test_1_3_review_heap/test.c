

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

//初始化
void init(HP* php)
{
	assert(php);
	php->a = NULL;
	php->capacity = php->size = 0;
}

//销毁
void destroy(HP* php)
{
	assert(php);
	free(php->a);
	php->capacity = php->size = 0;
}

//交换
void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//打印
void print(HP* php)
{
	assert(php);
	for (int i = 0; i < php->size; i++)
	{
		printf("%d ", php->a[i]);
	}
}


//向上调整
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

//插入数据
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

//判空
bool EmptyJudge(HP* php)
{
	assert(php);
	return php->size == 0;
}

//向下调整 - 小堆
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

//删除堆顶数据
void pop(HP* php)
{
	assert(php);
	assert(!EmptyJudge(php));

	swap(&php->a[0], &php->a[php->size - 1]);
	AdjustDown(php->a, php->size-1,0);
	php->size--;

}


//堆排序:升序:建大堆  降序:建小堆
//选数原理:每次将最大的换到最后,再向下调整
//向上调整建堆:时间复杂度:O(n*logn)
//向下调整建堆:时间复杂度:O(n)

//堆排序 - 升序 - 建大堆
void HeapSort(int* a,int n)
{
	//1.建堆 - 向下调整建堆
	//最后一个叶子结点的父结点就是最后一个非叶子结点
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}

	//2.选数 - 每次选择次大的数排在后面
	int i = 1;
	while (i<n)
	{
		swap(&a[0], &a[n - i]);
		AdjustDown(a, n - i, 0);
		i++;
	}

}

//topK问题
//选最大 - 建小堆
//建大堆:空间复杂度为O(N),如果是10亿个数选100个,无法在内存中完成
//建小堆:空间复杂度为O(K)

//建小堆思路:先建一个k个数的小堆,再把后n-k个数,依次和堆顶的数进行比较,比堆顶大,就交换,然后进行向下调整
void topk(int* a, int n,int k)
{
	//1.建小堆
	for (int i = (k - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a, k, i);
	}

	//2.取大数交换,向下调整
	for (int i = k; i < n; i++)
	{
		if (a[i] > a[0])
		{
			//swap(&a[i], &a[0]);  //这地方不用交换,赋值就行
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

	//HeapSort(a, sizeof(a) / sizeof(int));  //降序
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






















