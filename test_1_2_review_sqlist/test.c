

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef struct sqlist
{
	int* a;
	int size;
	int capacity;
}sqlist;



//打印
void print(sqlist* ps)
{
	assert(ps);
	int i = 0;
	while (i < ps->size)
	{
		printf("%d ", ps->a[i]);
		i++;
	}
}

//初始化
void init(sqlist* ps)
{
	assert(ps);
	ps->capacity = 0;
	//sqlist* a = (sqlist*)malloc(ps,ps->capacity*sizeof(sqlist));
	//if (a == NULL)
	//{
	//	perror("malloc fail);
	//	exit(-1);"
	//}
	ps->size = 0;
	ps->a = NULL;  //这一步不能忘了!

}

//销毁
void destroy(sqlist* ps)
{
	assert(ps);
	free(ps->a);
	ps->capacity = 0;
	ps->size = 0;
}


//判满
void FullJudge(sqlist* ps)
{
	assert(ps);
	if (ps->size == ps->capacity)
	{
		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		int* ptr = (int*)realloc(ps->a, newcapacity * sizeof(int));
		if (ptr == NULL)
		{
			perror("realloc fail");
			exit(-1);
		}
		ps->a = ptr;
		ps->capacity = newcapacity;
	}
}

//前插
void PushFront(sqlist* ps,int x)
{
	assert(ps);
	FullJudge(ps);

	int i = ps->size;
	while (i)
	{
		ps->a[i] = ps->a[i - 1];
		i--;
	}
	ps->a[0] = x;
	ps->size++;
}

//后插
void PushBack(sqlist* ps, int x)
{
	assert(ps);
	FullJudge(ps);
	ps->a[ps->size] = x;
	ps->size++;

}

bool EmptyJudge(sqlist* ps)
{
	assert(ps);

	return ps->size == 0;
}

//前删
void PopFront(sqlist* ps)
{
	assert(ps);
	assert(!EmptyJudge(ps));

	int i = 0;
	while (i < ps->size-1)
	{
		ps->a[i] = ps->a[i + 1];
		i++;
	}
	ps->size--;
}

//后删
void PopBack(sqlist* ps)
{
	assert(ps);
	assert(!EmptyJudge(ps));

	ps->size--;

}

//查
int Find(sqlist* ps,int x)
{
	assert(ps);

	int pos = 0;
	while (pos<ps->size)
	{
		if (ps->a[pos] = x)
		{
			return pos;
		}
		else
			pos++;
	}
	return -1;
}

//改
void Change(sqlist* ps, int x, int y)
{
	assert(ps);
	int pos = Find(ps, x);
	if (pos == -1)
	{
		return;
	}
	else
		ps->a[pos] = y;
}

//


int main()
{
	sqlist ps;
	init(&ps);
	PushFront(&ps, 1);
	PushFront(&ps, 2);
	PushFront(&ps, 3);
	PushFront(&ps, 4);
	PushFront(&ps, 5);
	
	PopFront(&ps);
	PopFront(&ps);
	PopFront(&ps);
	PopFront(&ps);
	PopFront(&ps);

	PushBack(&ps, 1);
	PushBack(&ps, 2);
	PopBack(&ps);

	/*int pos = Find(&ps, 1);
	printf("%d", pos);*/
	Change(&ps, 1, 2); //把1改成2
	print(&ps);

	//PushBack(&ps, 6);
	//PushBack(&ps, 7);
	//PushBack(&ps, 8);
	//PushBack(&ps, 9);
	//PushBack(&ps, 10);

	//print(&ps);


	return 0;
}




