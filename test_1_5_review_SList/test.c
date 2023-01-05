

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;

//��ʼ��
Node* BuyNode(int x)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	//�������ж�
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}

	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}

//����
void Destroy(Node** pps)
{
	assert(pps);
	Node* cur = *pps;
	while (cur)
	{
		Node* next = cur->next;
		free(cur);
		cur = next;
	}


	*pps = NULL;
}

//�п�
bool EmptyJudge(Node** pps)
{
	assert(pps);

	return *pps == NULL;

}

//��ӡ
void Print(Node** pps)
{
	assert(pps);
	//if (EmptyJudge(pps))
	//	return;
	//else
	//{
		Node* cur = *pps;
		while (cur)
		{
			printf("%d->", cur->data);
			cur = cur->next;
		}
		printf("NULL\n");
	//}

}


//ǰ�� -- ���÷���� ,ֱ�Ӳ�
void PushFront(Node** pps,int x)
{
	assert(pps);

	Node* newnode = BuyNode(x);
	//if (*ps == NULL)
	//{
	//	*ps = newnode;
	//}
	//else
	//{
		newnode->next = *pps;
		*pps = newnode;
	//}

}

//���  -- ��������� - �պͷǿ�
void PushBack(Node** pps, int x)
{
	assert(pps);

	Node* newnode = BuyNode(x);

	if (*pps == NULL)
	{
		*pps = newnode;
	}
	else
	{
		Node* cur = *pps;
		while (cur->next)
		{
			cur = cur->next;
		}
		cur->next = newnode;
	}


}



//ǰɾ -- ���÷����,ֱ��ɾ,ɾ��Ϊֹ
void PopFront(Node** pps)
{
	assert(pps);
	assert(!EmptyJudge(pps));

	Node* cur = *pps;
	*pps = (*pps)->next;
	free(cur);
	cur = NULL;

}

////��ɾ -- ��������� : һ�����,���������Ͻ��
//void PopBack(Node** pps)
//{
//	assert(pps);
//	assert(!EmptyJudge(pps));
//	
//	//ֻʣһ�����
//	if ((*pps)->next == NULL)
//	{
//		free(*pps);
//		(*pps) = NULL;
//	}
//	//���������Ͻ��
//	else
//	{
//		Node* tail = *pps;
//		while (tail->next->next)
//		{
//			tail = tail->next;
//		}
//		free(tail->next);
//		tail->next = NULL;
//	}
//
//}

//��ɾ -- ��������� : һ�����,���������Ͻ��
void PopBack(Node** pps)
{
	assert(pps);

	//ֻʣһ�����
	if ((*pps)->next == NULL)
	{
		free(*pps);
		*pps = NULL;
	}
	//���������Ͻ��
	else
	{
		Node* prev = NULL;//��һ��Ҫ��ס,�����벻���ĵ� ,Ūһ��ָ��յĽṹ��ָ��!

		Node* tail = *pps;
		while (tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		prev->next = NULL;
		free(tail);
		tail = NULL;

	}

}



//����+�޸�
Node* FindNode(Node** pps,int x)
{
	assert(pps);
	assert(!EmptyJudge(pps));

	Node* cur = *pps;
	while (cur)
	{
		if (cur->data == x)
			return cur;
		else
			cur = cur->next;
	}

	return NULL;
}

//posλ�ò���
void PushPos(Node** pps, Node* pos,int x)
{
	assert(pps);
	assert(pos);

	Node* newnode = BuyNode(x);
	Node* cur = *pps;
	if (*pps == NULL)
	{
		*pps = newnode;
	}
	else if (cur == pos)
	{
		PushFront(pps, x);
	}

	else
	{
		
		while (cur->next != pos&&cur)
		{
			cur = cur->next;
		}
		if (cur == NULL)
		{
			return;
		}
		else
		{
			newnode->next = pos;
			cur->next = newnode;
		}
	}
	
}



//posλ��ɾ��
void PopPos(Node** pps, Node* pos)
{
	assert(pps);
	assert(!EmptyJudge(pps));
	Node* cur = *pps;
	if (cur == pos)
	{
		PopFront(pps);
	}
	else
	{
		while (cur->next != pos && cur)
		{
			cur = cur->next;
		}
		if (cur == NULL)
		{
			return;
		}
		else
		{
			cur->next = pos->next;
			free(pos);
			pos = NULL;
		}
	}

	

}



//ע��!!!!!����ط����ô� Node** pps �������������!
//posλ�ú����
//����д��: ��Node** pps�������Ĳ���
void PushPosAfter(Node** pps, Node* pos,int x)
{
	assert(pps);
	assert(pos);

	Node* newnode = BuyNode(x);
	newnode->next = pos->next;
	pos->next = newnode;

}

//posλ�ú����
//��ȷд��:����Node* pps�������
void PushPosAfter( Node* pos, int x)
{
	assert(pos);

	Node* newnode = BuyNode(x);
	newnode->next = pos->next;
	pos->next = newnode;

}




//ͬ��!����ҪNode** pps�������!

//posλ�ú�ɾ��
//����д��: ��Node** pps�������Ĳ���
void PopPosAfter(Node** pps, Node* pos)
{
	assert(pps);
	assert(pos);

	Node* next = pos->next;
	pos->next = next->next;
	free(next);
	next = NULL;
}

//��ȷд��: û��Node** pps �������
void PopPosAfter( Node* pos)
{
	assert(pos);

	Node* next = pos->next;
	pos->next = next->next;
	free(next);
	next = NULL;
}


int main()
{
	//Node* n1 = BuyNode(1);
	//Node* n2 = BuyNode(2);

	//n1->next = n2;
	//Destroy(&n1);
	Node* ps = NULL;
	//PushFront(&ps, 1);
	//PushFront(&ps, 2);
	//PushFront(&ps, 3);
	//PushFront(&ps, 4);
	//PushFront(&ps, 5);
	//PushFront(&ps, 6);
	//PushFront(&ps, 7);

	PushBack(&ps, 8);
	PushBack(&ps, 9);
	PushBack(&ps, 10);

	//PopFront(&ps);
	//PopFront(&ps);
	//PopFront(&ps);
	//PopFront(&ps);
	//PopBack(&ps);
	//PopBack(&ps);
	//PopBack(&ps);
	//PopBack(&ps);

	Node* pos = FindNode(&ps, 9);
	//printf("%d\n", pos->data);
	PopPosAfter(&ps, pos);
	PushPosAfter(&ps, pos, 11);
	PopPos(&ps, pos);
	pos = FindNode(&ps, 8);
	PushPos(&ps, pos, 100);
	//PushPos(&ps, pos, 1);
	Print(&ps);

	return 0;
}



