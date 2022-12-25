
#include<stdio.h>
#include<assert.h>


SLNode* BuySLNode(int x);       //创建一个单链表结点
void SListPrint(SLNode* phead);          //单链表打印
void SListDestory(SLNode** pphead);      //单链表销毁
void SListPushFront(SLNode** pphead, int x);  //单链表头插 (struct SListNode** pphead,int x)
void SListPushBack(SLNode** pphead, int x);   //单链表尾插
void SListPopBack(SLNode** pphead);      //单链表尾删
void SListPopFront(SLNode** pphead);     //单链表头删

SLNode* SListFind(SLNode* phead, int x);   //单链表元素查找  返回该结点地址

// 在pos之前插入
void SListInsert(SLNode** pphead, SLNode* pos, int x);  //在pos前插入

// 在pos后面插入
void SListInsertAfter(SLNode* pos, int x);  //在pos后插入

// 删除pos位置
void SListErase(SLNode** pphead, SLNode* pos);  //删除pos位置的结点

// 删除pos后面位置
void SListEraseAfter(SLNode* pos);  //删除pos后面位置的结点


typedef struct SLNode
{
	int data;
	struct SLNode* next;
}SLNode;


//删除pos后面位置的结点
void SListEraseAfter(SLNode* pos)
{
	if (pos->next == NULL)
	{
		return;
	}

	SLNode* next = pos->next;
	pos->next = next->next;
	free(next);
	next = NULL;
}


//删除pos位置的结点
void SListErase(SLNode** pphead, SLNode* pos)
{
	assert(pphead);

	if (*pphead == pos)
	{
		SListPopFront(pphead, pos);
	}
	else
	{
		SLNode* pre = *pphead;
		while (pre->next != pos)
		{
			pre = pre->next;
			assert(pre);
		}

		pre->next = pos->next;
		free(pos);
		pos = NULL;
	}

	
}

//在pos后插入
void SListInsertAfter(SLNode* pos, int x)
{
	assert(pos);

	SLNode* newnode = BuySLNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}


//在pos前插入
void SListInsert(SLNode** pphead, SLNode* pos, int x)
{
	//写的有问题,未考虑到首插很容易
	/*assert(pphead);
	SLNode* cur = *pphead;
	SLNode* newnode = BuySLNode(x);
	while (cur->next != pos)
	{
		cur = cur->next;
		assert(cur);
	}
	newnode->next = pos;
	cur->next = newnode;*/

	assert(pphead);
	assert(pos);

	if (pos == *pphead)
	{
		SListPushFront(pphead, x);
	}
	else
	{
		SLNode* pre = *pphead;
		while (pre->next != pos);
		{
			pre = pre->next;

			assert(pre);
		}

		SLNode* newnode = BuySLNode(x);
		pre->next = newnode;
		newnode->next = pos;
	}
}


//单链表元素查找  返回该结点地址
SLNode* SListFind(SLNode* phead, int x)
{
	SLNode* cur = phead;
	while (cur != NULL)
	{
		if (cur->data == x)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}


//单链表头删
void SListPopFront(SLNode** pphead)
{
	assert(pphead);

	if (*pphead == NULL)
	{
		return;
	}

	//也实现了
	/*if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SLNode* cur = *pphead;
		*pphead = (*pphead)->next;
		free(cur);
		cur = NULL;
	}*/

	//但实际上不需要分情况
	SLNode* del = *pphead;
	*pphead = (*pphead)->next;
	free(del);
	del = NULL;
}


//单链表尾删
void SListPopBack(SLNode** pphead)
{
	assert(pphead);

	//方法一
	//if (*pphead == NULL)
	//{
	//	return;
	//}
	//else if ((*pphead)->next == NULL)   //这里要注意,要加上(),因为*和->的优先级相同
	//{
	//	free(*pphead);
	//	*pphead = NULL;
	//}
	//else
	//{
	//	SLNode* tail = *pphead;
	//	while (tail->next->next != NULL)
	//	{
	//		tail = tail->next;
	//	}
	//	free(tail->next);
	//	tail->next = NULL;

	//}

	//方法二:
	if (*pphead == NULL)
	{
		return;
	}
	else if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SLNode* tail = *pphead;
		SLNode* pre = NULL;
		while (tail->next != NULL)
		{
			pre = tail;
			tail = tail->next;
		}
		free(pre->next);
		pre->next = NULL;
		tail = NULL;
	}
}


//单链表尾插
void SListPushBack(SLNode** pphead, int x)
{
	assert(pphead);
	SLNode* newnode = BuySLNode(x);
	//第一次
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		//找尾
		SLNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}

		tail->next = newnode;
	}
}


//单链表头插 (struct SListNode** pphead,int x)
void SListPushFront(SLNode** pphead, int x)
{
	assert(pphead);

	//也实现了
	/*SLNode* newnode = BuySLNode(x);
	if (*pphead == NULL)
	{
		pphead = newnode;
	}
	else
	{
		newnode->next = *pphead;
		*pphead = newnode;
	}*/

	//实际上不需要分空和非空
	SLNode* newnode = BuySLNode(x);
	newnode->next = *pphead;
	*pphead = newnode;
}




//单链表销毁
void SListDestory(SLNode** pphead)
{
	assert(pphead);
	SLNode* cur = *pphead;
	SLNode* pre = NULL;
	while (cur != NULL)
	{
		pre = cur;
		cur = cur->next;
		free(pre);
		pre->next = NULL;
	}
}



//单链表打印
void SListPrint(SLNode* phead)
{
	/*if (phead == NULL)
	{
		return;
	}
	while (phead->next != NULL)
	{
		printf("%d", phead->data);
		phead = phead->next;
	}
	printf("%d->NULL", phead->data);*/

	SLNode* cur = phead;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}


//创建一个单链表结点
SLNode* BuySLNode(int x)
{
	/*SLNode newnode;
	newnode.data = x;
	newnode.next = NULL;
	return &newnode;*/
	SLNode* newnode = (SLNode*)malloc(sizeof(SLNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}

int main()
{
	

	return 0;
}