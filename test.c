
#include<stdio.h>
#include<assert.h>


SLNode* BuySLNode(int x);       //����һ����������
void SListPrint(SLNode* phead);          //�������ӡ
void SListDestory(SLNode** pphead);      //����������
void SListPushFront(SLNode** pphead, int x);  //������ͷ�� (struct SListNode** pphead,int x)
void SListPushBack(SLNode** pphead, int x);   //������β��
void SListPopBack(SLNode** pphead);      //������βɾ
void SListPopFront(SLNode** pphead);     //������ͷɾ

SLNode* SListFind(SLNode* phead, int x);   //������Ԫ�ز���  ���ظý���ַ

// ��pos֮ǰ����
void SListInsert(SLNode** pphead, SLNode* pos, int x);  //��posǰ����

// ��pos�������
void SListInsertAfter(SLNode* pos, int x);  //��pos�����

// ɾ��posλ��
void SListErase(SLNode** pphead, SLNode* pos);  //ɾ��posλ�õĽ��

// ɾ��pos����λ��
void SListEraseAfter(SLNode* pos);  //ɾ��pos����λ�õĽ��


typedef struct SLNode
{
	int data;
	struct SLNode* next;
}SLNode;


//ɾ��pos����λ�õĽ��
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


//ɾ��posλ�õĽ��
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

//��pos�����
void SListInsertAfter(SLNode* pos, int x)
{
	assert(pos);

	SLNode* newnode = BuySLNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}


//��posǰ����
void SListInsert(SLNode** pphead, SLNode* pos, int x)
{
	//д��������,δ���ǵ��ײ������
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


//������Ԫ�ز���  ���ظý���ַ
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


//������ͷɾ
void SListPopFront(SLNode** pphead)
{
	assert(pphead);

	if (*pphead == NULL)
	{
		return;
	}

	//Ҳʵ����
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

	//��ʵ���ϲ���Ҫ�����
	SLNode* del = *pphead;
	*pphead = (*pphead)->next;
	free(del);
	del = NULL;
}


//������βɾ
void SListPopBack(SLNode** pphead)
{
	assert(pphead);

	//����һ
	//if (*pphead == NULL)
	//{
	//	return;
	//}
	//else if ((*pphead)->next == NULL)   //����Ҫע��,Ҫ����(),��Ϊ*��->�����ȼ���ͬ
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

	//������:
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


//������β��
void SListPushBack(SLNode** pphead, int x)
{
	assert(pphead);
	SLNode* newnode = BuySLNode(x);
	//��һ��
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		//��β
		SLNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}

		tail->next = newnode;
	}
}


//������ͷ�� (struct SListNode** pphead,int x)
void SListPushFront(SLNode** pphead, int x)
{
	assert(pphead);

	//Ҳʵ����
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

	//ʵ���ϲ���Ҫ�ֿպͷǿ�
	SLNode* newnode = BuySLNode(x);
	newnode->next = *pphead;
	*pphead = newnode;
}




//����������
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



//�������ӡ
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


//����һ����������
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