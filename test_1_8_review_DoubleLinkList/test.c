
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

////��ʼ��
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


//��ʼ��
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

//�������
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


//��ӡ
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


//����
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

//pos����
//ͷ��,pos = pd->next
//β��,pos = pd
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


////posɾ��
////ͷɾ:pos = pd->next;
////βɾ:pos = pd->prev;
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


//ע��!!!!!
//�����pos�����posɾ������д�鷳��,����Ч�ʱ����!
//˫��������,
//1.����������pos�Ժ�,���ǾͲ���Ҫԭ�����ͷ�����,��Ϊpos����һ��ָ�������ָ��,�����ҵ��Ǹ�˫������
//     (��һ��������Ҳ��һ��,ֻ������������Ȼ��Ҫͷ�������ҵ�pos��ǰһ�����)
//(��Ҫ!)2.����������pos�Ժ�,��˫������,���ǲ�����Ҫ����ȥ��pos,ֱ��ͨ��pos��next��prev�ҵ�ǰ������в����ɾ��

//����ֻ��posǰ���
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

//ɾ����Ҫposǰ,���������
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

//ͷ��
PushFront(DL* pd,int x)
{
	PushPos(pd->next,x);
}

//ͷɾ
PopFront(DL* pd)
{
	assert(!EmptyJudge(pd));
	PopPos(pd->next);
}

//β��
PushBack(DL* pd, int x)
{
	PushPos(pd, x);
}

//βɾ
PopBack(DL* pd)
{
	assert(!EmptyJudge(pd));
	PopPos(pd->prev);
}


//�����С
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

//����
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











