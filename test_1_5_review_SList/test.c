

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;

//初始化
Node* BuyNode(int x)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	//别忘了判断
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}

	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}

//销毁
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

//判空
bool EmptyJudge(Node** pps)
{
	assert(pps);

	return *pps == NULL;

}

//打印
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


//前插 -- 不用分情况 ,直接插
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

//后插  -- 分两种情况 - 空和非空
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



//前删 -- 不用分情况,直接删,删空为止
void PopFront(Node** pps)
{
	assert(pps);
	assert(!EmptyJudge(pps));

	Node* cur = *pps;
	*pps = (*pps)->next;
	free(cur);
	cur = NULL;

}

////后删 -- 分两种情况 : 一个结点,两个及以上结点
//void PopBack(Node** pps)
//{
//	assert(pps);
//	assert(!EmptyJudge(pps));
//	
//	//只剩一个结点
//	if ((*pps)->next == NULL)
//	{
//		free(*pps);
//		(*pps) = NULL;
//	}
//	//两个及以上结点
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

//后删 -- 分两种情况 : 一个结点,两个及以上结点
void PopBack(Node** pps)
{
	assert(pps);

	//只剩一个结点
	if ((*pps)->next == NULL)
	{
		free(*pps);
		*pps = NULL;
	}
	//两个及以上结点
	else
	{
		Node* prev = NULL;//这一步要记住,是我想不到的点 ,弄一个指向空的结构体指针!

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



//查找+修改
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

//pos位置插入
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



//pos位置删除
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



//注意!!!!!这个地方不用传 Node** pps 这个参数进来了!
//pos位置后插入
//错误写法: 有Node** pps这个多余的参数
void PushPosAfter(Node** pps, Node* pos,int x)
{
	assert(pps);
	assert(pos);

	Node* newnode = BuyNode(x);
	newnode->next = pos->next;
	pos->next = newnode;

}

//pos位置后插入
//正确写法:不用Node* pps这个参数
void PushPosAfter( Node* pos, int x)
{
	assert(pos);

	Node* newnode = BuyNode(x);
	newnode->next = pos->next;
	pos->next = newnode;

}




//同理!不需要Node** pps这个参数!

//pos位置后删除
//错误写法: 有Node** pps这个多余的参数
void PopPosAfter(Node** pps, Node* pos)
{
	assert(pps);
	assert(pos);

	Node* next = pos->next;
	pos->next = next->next;
	free(next);
	next = NULL;
}

//正确写法: 没有Node** pps 这个参数
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



