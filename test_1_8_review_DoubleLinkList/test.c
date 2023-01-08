
#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNode
{
	struct ListNode* next;
	struct ListNode* prev;
	int data;
}DL;

////初始化
//void init(DL** pd)
//{
//	DL* guard = (DL*)malloc(sizeof(DL));
//	if (guard == NULL)
//	{
//		perror("malloc fial");
//		exit(-1);
//	}
//
//	guard->next = guard;
//	guard->prev = guard;
//
//	*pd = guard;
//}


//初始化
DL* Init()
{
	DL* guard = (DL*)malloc(sizeof(DL));
	if (guard == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}

	guard->next = guard;
	guard->prev = guard;

	return guard;
}

//创建结点
DL* BuyNode(int x)
{
	DL* newnode = (DL*)malloc(sizeof(DL));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}

	newnode->data = x;
	newnode->next = newnode;
	newnode->prev = newnode;

	//
	return newnode;
}


//打印
void Print(DL* pd)
{
	DL* cur = pd->next;
	while (cur != pd)
	{
		printf("%d<=>", cur->data);
	}
		cur = cur->next;
	printf("\n");

}


//查找
DL* Find(DL* pd, int x)
{
	DL* cur = pd->next;
	while (cur != pd)
	{
		if (cur->data == x)
		{
			return cur;
		}
		cur = cur->next;
	}

	return NULL;
}

//pos插入
//头插,pos = pd->next
//尾插,pos = pd
//void PushPos(DL* pd, int x,DL* pos)
//{
//	DL* cur = pd->next;
//	DL* newnode = BuyNode(x);
//	if (pos == pd)
//	{
//		newnode->prev = pd->prev;
//		pd->prev->next = newnode;
//		newnode->next = pd;
//		pd->prev = newnode;
//		return;
//	}
//
//	while (cur != pd)
//	{
//		if (cur == pos)
//		{
//			newnode->prev = cur->prev;
//			cur->prev->next = newnode;
//			newnode->next = cur;
//			cur->prev = newnode;
//			return;
//		}
//		else
//		{
//			cur = cur->next;
//		}
//	}
//
//}


////pos删除
////头删:pos = pd->next;
////尾删:pos = pd->prev;
//void PopPos(DL* pd, DL* pos)
//{
//	DL* cur = pd->next;
//	if (pos == pd->prev)
//	{
//		pos->prev->next = pos->next;
//		pos->next->prev = pos->prev;
//		free(pos);
//		pos->prev = NULL;
//		pos->next = NULL;
//		return;
//	}
//
//	while (cur != pd)
//	{
//		if (cur == pos)
//		{
//			cur->prev->next = cur->next;
//			cur->next->prev = cur->prev;
//			free(pos);
//			pos->prev = NULL;
//			pos->next = NULL;
//			return;
//		}
//		else
//		{
//			cur = cur->next;
//		}
//	}
//
//}


//注意!!!!!
//上面的pos插入和pos删除不仅写麻烦了,而且效率变低了!
//双向链表中,
//1.当我们有了pos以后,我们就不需要原链表的头结点了,因为pos就是一个指向链表的指针,可以找到那个双向链表
//     (这一条单链表也是一样,只不过单链表依然需要头结点遍历找到pos的前一个结点)
//(重要!)2.当我们有了pos以后,在双链表中,我们不再需要遍历去找pos,直接通过pos的next和prev找到前后结点进行插入和删除

//插入只需pos前结点
void PushPos(DL* pos, int x)
{
	DL* prev = pos->prev;

	DL* newnode = BuyNode(x);
	prev->next = newnode;
	newnode->next = pos;
	pos->prev = newnode;
	newnode->prev = prev;
}

bool EmptyJudge(DL* pd)
{
	return pd->next == pd && pd->prev == pd;
}

//删除需要pos前,后两个结点
void PopPos(DL* pos)
{
	assert(pos);
	DL* prev = pos->prev;
	DL* next = pos->next;

	prev->next = next;
	next->prev = prev;
	free(pos);
	pos->next = NULL;
	pos->prev = NULL;

}

//头插
PushFront(DL* pd,int x)
{
	PushPos(pd->next,x);
}

//头删
PopFront(DL* pd)
{
	assert(!EmptyJudge(pd));
	PopPos(pd->next);
}

//尾插
PushBack(DL* pd, int x)
{
	PushPos(pd, x);
}

//尾删
PopBack(DL* pd)
{
	assert(!EmptyJudge(pd));
	PopPos(pd->prev);
}


//链表大小
int DListSize(DL* pd)
{
	DL* cur = pd->next;
	int count = 0;
	while (cur != pd)
	{
		count++;
		cur = cur->next;
	}

}

//销毁
Destroy(DL* pd)
{
	DL* cur = pd->next;
	while (cur!=pd)
	{
		DL* del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
	free(pd);

}


int main()
{
	DL* pd = Init();
	PushPos(pd, 1);
	PushPos(pd, 2);
	PushPos(pd, 3);
	PushPos(pd, 4);
	PushPos(pd, 5);
	PushPos(pd, 6);

	//PopPos(pd->next);
	PopFront(pd);
	PopBack(pd);
	PushFront(pd, 10);
	PushBack(pd, 20);

	Print(pd);

	Destroy(pd);

	Print(pd);

	return 0;
}











