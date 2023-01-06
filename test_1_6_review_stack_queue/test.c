

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef struct stack
{
	int* a;
	int size;
	int capacity;
}ST;
//
////��ӡ
//void Print(ST* ps)
//{
//	for (int i = 0; i < ps->size; i++)
//	{
//		printf("%d ", ps->a[i]);
//	}
//	printf("\n");
//}
//
//
////��ʼ��
//void init(ST* ps)
//{
//	ps->a = NULL;
//	ps->size = ps->capacity = 0;
//}
//
////��ջ - ��������������
//void Push(ST* ps,int x)
//{
//	//��������
//	if (ps->size == ps->capacity)
//	{
//		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
//		int* tmp = (int*)realloc(ps->a, sizeof(int) * newcapacity);
//		if (tmp == NULL)
//		{
//			perror("realloc fail");
//			exit(-1);
//		}
//
//		ps->a = tmp;
//		ps->capacity = newcapacity;
//
//	}
//
//	ps->a[ps->size] = x;
//	ps->size++;
//}
//
////�п�
//bool EmptyJudge(ST* ps)
//{
//	return ps->size == 0;
//}
//
////��ջ - �пհ���������
//void Pop(ST* ps)
//{
//	assert(!EmptyJudge(ps));
//	
//	ps->size--;
//}
//
//
////����
//void Destroy(ST* ps)
//{
//	free(ps->a);
//	ps->a = NULL;
//	ps->capacity = ps->size = 0;
//
//}
//
////��ջ��
//int StackBottom(ST* ps)
//{
//	assert(!EmptyJudge(ps));
//	return ps->a[0];
//}
//
//
////��ջ��
//int StackTop(ST* ps)
//{
//	assert(!EmptyJudge(ps));
//	return ps->a[ps->size - 1];
//}
//
////ջ�Ĵ�С
//int StackSize(ST* ps)
//{
//	return ps->size;
//}



typedef struct QueueNode
{
	struct QueueNode* next;
	int data;
}QNode;

typedef struct Queue
{
	QNode* head;
	QNode* tail;
	int size;
}Queue;


//��ʼ��
void init(Queue* pq)
{
	pq->head = pq->tail = NULL;

	pq->size = 0;
}

//��ӡ
void Print(Queue* pq)
{
	QNode* cur = pq->head;
	while (cur)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}


//�����
Push(Queue* pq, int x)
{
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}
	else
	{
		newnode->data = x;
		newnode->next = NULL;
	}

	//���������:�޽��,�нڵ�
	if (pq->tail == NULL)
	{
		pq->head = pq->tail = newnode;
	}
	else
	{
		pq->tail->next = newnode;
		pq->tail = pq->tail->next;
	}

	pq->size++;

}

bool EmptyJudge(Queue* pq)
{
	//return pq->size == 0;
	return pq->head == NULL && pq->tail == NULL;
}

//������
void Pop(Queue* pq)
{
	assert(pq);
	assert(!EmptyJudge(pq));

	//���������:һ�����,���������Ͻ��
	if (pq->head->next==NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else
	{
		QNode* del = pq->head;
		pq->head = pq->head->next;
		free(del);
		del = NULL;
	}
	pq->size--;

}


//����
void Destroy(Queue* pq)
{
	QNode* cur = pq->head;
	while (cur)
	{
		QNode* del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
	pq->head = pq->tail = NULL;

}


//��ͷ
int QFront(Queue* pq)
{
	assert(!EmptyJudge(pq));

	return pq->head->data;
}

//��β
int QBack(Queue* pq)
{
	assert(!EmptyJudge(pq));

	return pq->tail->data;
}


//���г���
int QSize(Queue* pq)
{
	return pq->size;
}




//void Test1()
//{
//	ST st;
//	init(&st);
//	Push(&st, 1);
//	Push(&st, 2);
//	Push(&st, 3);
//	Push(&st, 4);
//	Push(&st, 5);
//	Push(&st, 6);
//
//	Print(&st);
//
//	Pop(&st);
//
//	Print(&st);
//
//	Destroy(&st);
//
//	Print(&st);
//}

void Test2()
{
	Queue pq;
	init(&pq);
	Push(&pq, 1);
	Push(&pq, 2);
	Push(&pq, 3);
	Push(&pq, 4);
	Push(&pq, 5);
	Push(&pq, 6);

	Print(&pq);

	Pop(&pq);
	Pop(&pq);
	Pop(&pq);

	Print(&pq);

	Destroy(&pq);

	Print(&pq);

}

int main()
{
	//Test1();

	Test2();
	return 0;
}














































