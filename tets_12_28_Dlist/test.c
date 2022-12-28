#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int LTDateType;

typedef struct ListNode
{
	struct ListNode* next;
	struct ListNode* prev;
	LTDateType data;
}LTNode;


//链表初始化,自己要跟自己循环
LTNode* ListInit()
{
	LTNode* guard = (LTNode*)malloc(sizeof(LTNode));
	if (guard == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}

	guard->next = guard;
	guard->prev = guard;

	return guard;
}

//买一个结点
LTNode* BuyListNode(LTDateType x)
{
	LTNode* node = (LTNode*)malloc(sizeof(LTNode));
	if (node == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}

	node->next = NULL;
	node->prev = NULL;
	return node;
}

//尾插
//1.不用找尾
//2.不用管链表是否为空
void ListPushBack(LTNode* phead, LTDateType x)
{
	assert(phead);

	LTNode* newnode = BuyListNode(x);
	LTNode* tail = phead->prev;

	tail->next = newnode;
	newnode->prev = tail;
	newnode->next = phead;
	phead->prev = newnode;

}

//链表打印
void ListPrint(LTNode* phead)
{
	assert(phead);
	printf("phead<=>");
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		printf("%d<=>", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

//头插
void ListPushFront(LTNode* phead, LTDateType x)
{
	assert(phead);

	LTNode* newnode = BuyListNode(x);
	////这个地方要注意顺序!这两个必须先写
	//newnode->next = phead->next;
	//phead->next->prev = newnode;

	//phead->next = newnode;
	//newnode->prev = phead;

	//下面是不需要管顺序的写法
	LTNode* first = phead->next;
	phead->next = newnode;
	newnode->prev = phead;
	phead->next = first;
	first->prev = newnode;
}

//判空
bool ListEmpty(LTNode* phead)
{
	assert(phead);

	/*if (phead->next == phead)
	{
		return true;
	}
	else
		return false;*/

	return phead->next == phead;
}


//尾删
void ListPopBack(LTNode* phead)
{
	assert(phead);
	assert(!ListEmpty(phead)); //判空,是不是删完了只剩下哨兵位头结点了

	LTNode* tail = phead->prev;
	LTNode* prev = tail->prev;  //找到尾的前一个

	prev->next = phead;
	phead->prev = prev;
	free(tail);
	tail = NULL;
}

//头删
void ListPopFront(LTNode* phead)
{
	assert(phead);
	assert(!ListEmpty(phead));

	LTNode* first = phead->next;
	LTNode* second = phead->next->next;

	phead->next = second;
	second->prev = phead;

	free(first);
	first = NULL;

}

//计算链表长度
size_t ListSize(LTNode* phead)
{
	assert(phead);

	size_t n = 0;
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		++n;
		cur = cur->next;
	}
	return n;
}

//结点查找/修改
LTNode* ListFind(LTNode* phead,LTDateType x)
{
	assert(phead);

	LTNode* cur = phead->next;
	while (cur != phead)
	{
		if (cur->data == x)
		{
			return cur;
		}
		cur = cur->next;
	}

	return NULL;
}




//在pos之前插入
void ListInsert(LTNode* pos, LTDateType x)
{
	assert(pos);

	LTNode* prev = pos->prev;
	LTNode* newnode = BuyListNode(x);

	//
	prev->next = newnode;
	newnode->prev = prev;
	newnode->next = pos;
	pos->prev = newnode;
}


//在pos前删除
void ListErase(LTNode* pos)
{
	assert(pos);

	LTNode* prev = pos->prev;
	LTNode* next = pos->next;

	prev->next = next;
	next->prev = prev;
	free(pos);
	pos = NULL;


}


//头插
void ListPushFront(LTNode* phead, LTDateType x)
{
	assert(phead);
	ListInsert(phead->next, x);
}


//尾插
void ListPushBack(LTNode* phead, LTDateType x)
{
	assert(phead);
	ListInsert(phead, x);
}

//头删
void ListPopFront(LTNode* phead)
{
	assert(phead);
	ListErase(phead->next);
}


//尾删
void ListPopBack(LTNode* phead)
{
	assert(phead);
	ListErase(phead->prev);
}

void ListDestroy(LTNode* phead)
{
	assert(phead);

	LTNode* cur = phead->next;
	while (cur != phead)
	{
		LTNode* next = cur->next;
		free(cur);
		cur = next;
	}
	free(phead);
	//phead = NULL
}


