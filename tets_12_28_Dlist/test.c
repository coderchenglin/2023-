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


//�����ʼ��,�Լ�Ҫ���Լ�ѭ��
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

//��һ�����
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

//β��
//1.������β
//2.���ù������Ƿ�Ϊ��
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

//�����ӡ
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

//ͷ��
void ListPushFront(LTNode* phead, LTDateType x)
{
	assert(phead);

	LTNode* newnode = BuyListNode(x);
	////����ط�Ҫע��˳��!������������д
	//newnode->next = phead->next;
	//phead->next->prev = newnode;

	//phead->next = newnode;
	//newnode->prev = phead;

	//�����ǲ���Ҫ��˳���д��
	LTNode* first = phead->next;
	phead->next = newnode;
	newnode->prev = phead;
	phead->next = first;
	first->prev = newnode;
}

//�п�
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


//βɾ
void ListPopBack(LTNode* phead)
{
	assert(phead);
	assert(!ListEmpty(phead)); //�п�,�ǲ���ɾ����ֻʣ���ڱ�λͷ�����

	LTNode* tail = phead->prev;
	LTNode* prev = tail->prev;  //�ҵ�β��ǰһ��

	prev->next = phead;
	phead->prev = prev;
	free(tail);
	tail = NULL;
}

//ͷɾ
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

//����������
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

//������/�޸�
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




//��pos֮ǰ����
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


//��posǰɾ��
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


//ͷ��
void ListPushFront(LTNode* phead, LTDateType x)
{
	assert(phead);
	ListInsert(phead->next, x);
}


//β��
void ListPushBack(LTNode* phead, LTDateType x)
{
	assert(phead);
	ListInsert(phead, x);
}

//ͷɾ
void ListPopFront(LTNode* phead)
{
	assert(phead);
	ListErase(phead->next);
}


//βɾ
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


