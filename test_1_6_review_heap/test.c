


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

//堆:顺序存储

typedef struct heap
{
	int* a;
	int size;
	int capacity;
}HP;

//初始化
void init(HP* php)
{
	php->a = NULL;
	php->capacity = php->size = 0;
}

//销毁
void destroy(HP* php)
{
	free(php->a);
	php->capacity = php->size = 0;
	php = NULL;
}

//交换
void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//打印
void Print(HP* php)
{
	for (int i = 0; i < php->size; i++)
	{
		printf("%d ", php->a[i]);
	}
	printf("\n");
}

//向上调整 - 建小堆
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

//给动态开辟的数据插入数据,要记得,是要判满的!
//正常情况下,给一个动态开辟的数组存数据,是要写一个'判满'函数的,
//但是这个地方只有插入数据一个要用到判满,所以直接写进去了

//兄弟!你tm判满用malloc????
//肯定用realloc啊,要不然怎么改怎么大小啊,用malloc每次一满就新开一个嘛?!

//插入数据 - 建小堆
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

//判空
bool JudgeVoid(HP* php)
{
	return php->size == 0;
}

//向下调整 -- 小堆
//参数的作用:
//int size可以控制向下调整到什么位置(即参与到向下调整的最后元素的下标+1) -- 堆排序需要这个参数
//int parent可以控制是哪个根向下调整
//
//应用:
//1.删除堆顶元素
//2.堆排序  -- 需要用到int size这个参数
//3.建堆

//新感悟:向下调整,不需要传一个堆进来呀!是个数组就行呀
void AdjustDown(int* a,int parent,int size) 
{
	int minchild = parent * 2 + 1;
	//选小的儿子交换
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


//删除堆顶数据
Pop(HP* php)
{
	assert(!JudgeVoid(php));
	Swap(&php->a[0], &php->a[php->size - 1]);
	AdjustDown(php->a, 0,php->size-1);
	php->size--;

}

//堆排序 - 降序 - 建小堆

//感悟二:堆排序不用传一个堆进来呀!为啥非要堆才能排,是个数组就可以排了呀!
//a是数组,size是元素个数
void HeapSort(int* a,int size)
{
	while (size > 0)  //注意这个地方不能等于0,要不然a[size-1]就是a[-1],就越界了
	{
		Swap(&a[0],&a[size-1]);
		AdjustDown(a, 0, size-1);
		size--;
	}
}


//建堆
//向上调整建堆 - 小堆
//void UpCreatHeap(int* a,int size)
//{
//	for (int i = 0; i < size; i++)
//	{
//		Push(a, a[i]);
//	}
//
//}

//向下调整建堆 - 从最后一个非叶子结点开始,向下调整建堆 - 小堆
void DownCreatHeap(int* a, int size)
{
	for (int i = (size - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, i, size);
	}

}


//topk问题 - 最大 - 建小堆
void TOPK(int* a,int k,int n)
{
	//建一个k个元素大小的小堆
	DownCreatHeap(a, n);

	//把后面的n-k个元素,往后依次插入,将大的放进去沉底
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
	////降序:8 7 6 5 4 3 2 1

	int b[] = { 8,7,6,5,4,3,2,1 };
	//DownCreatHeap(b, 8);
	//for (int i = 0; i < sizeof(b) / sizeof(int); i++)
	//{
	//	printf("%d ", b[i]);
	//}
	//printf("\n");
	//b小堆:1 4 2 5 8 3 6 7

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
//	//HeapSort(a, sizeof(a) / sizeof(int));  //降序
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





























