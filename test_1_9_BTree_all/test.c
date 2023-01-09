

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int BTDataType;
typedef struct BinaryTree
{
	struct BinaryTree* left;
	struct BinaryTree* right;
	BTDataType data;
}BTNode;

typedef BTNode* QueueDataType;
//队列是拿链表实现的
typedef struct QNode
{
	struct QNode* next;
	QueueDataType data;
}QNode;

typedef struct Queue
{
	QNode* head;
	QNode* tail;
	int size;
}Queue;



//队列初始化(给链表的初始化)
void QInit(Queue* pq)
{
	pq->head = pq->tail = NULL;
	pq->size = 0;
}

//销毁
void QDestroy(Queue* pq)
{
	QNode* cur = pq->head;
	while (cur)
	{
		QNode* del = cur;
		cur = cur->next;
		free(del);
	}
	pq->head = pq->tail = NULL;
	pq->size = 0;

	//这里不能free(pq)
}


//入队尾(包括判满)
void QPush(Queue* pq, QueueDataType x)
{
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;

	if (pq->tail == NULL)
	{
		pq->tail = pq->head = newnode;
	}
	else
	{
		pq->tail->next = newnode;
		pq->tail = newnode;
	}

	pq->size++;
}

//判空
bool QEmptyJudge(Queue* pq)
{
	return pq->tail == NULL;
}


//出队头
void QPop(Queue* pq)
{
	assert(!QEmptyJudge(pq));

	if (pq->head->next == NULL)
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


//队头元素
QueueDataType QFront(Queue* pq)
{
	assert(!QEmptyJudge(pq));
	return pq->head->data;
}


//队尾元素
QueueDataType QBack(Queue* pq)
{
	assert(!QEmptyJudge(pq));
	return pq->tail->data;
}


//队列大小
int QSize(Queue* pq)
{
	return pq->size;
}


//----------------------


//二叉树前序遍历
void PreOrder(BTNode* root)
{
	if (root == NULL)
		return;

	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}


//二叉树中序遍历
void InOrder(BTNode* root)
{
	if (root == NULL)
		return;

	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);
}


// 二叉树后序遍历
void PostOrder(BTNode* root)
{
	if (root == NULL)
		return;

	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
}


//树大小
int TreeSize(BTNode* root)
{
	if (root == NULL)
		return 0;

	return TreeSize(root->left) + TreeSize(root->right) + 1;

}


//叶子数
int LeafSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}

	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}

	return TreeSize(root->left) + TreeSize(root->right);

}


//树高度
int TreeHight(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}

	int lret = TreeHight(root->left);
	int rret = TreeHight(root->right);

	return lret > rret ? lret + 1 : rret + 1;
}


//第k层结点个数
int TreeKSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;

	if (k == 1)
		return 1;

	return TreeKSize(root->left, k - 1) + TreeKSize(root->right, k - 1);

}


//返回x所在的结点
BTNode* FindTreeNode(BTNode* root, BTDataType x)
{
	if (root == NULL)
		return NULL;

	if (root->data == x)
	{
		BTNode* ret = root;
		return ret;
	}

	BTNode* lret = FindTreeNode(root->left, x);
	if (lret)
		return lret;
	BTNode* rret = FindTreeNode(root->right, x);
	if (rret)
		return rret;

	return NULL;
}


//下面是非递归应用

//层序遍历
void LevelOrder(BTNode* root)
{
	//错误的定义!!
	//Queue* pq = NULL;
	//解释:1.我直接定义一个指针出来,没有置空,就是没有初始化,置空,地址就为空,为空的指针后序如何解引用呢?
	//     2.我只能先定义一个结构体,然后取他的地址,后序对这个地址解引用,才能对我
	//正确的定义:
	//Queue pq;
	Queue pq;
	QInit(&pq);
	if (root != NULL)
	{
		//注意,反思:我往队列里面放的是二叉树的指针!不是二叉树里面的data!
		//不要把这个搞混了!!!!!!!!!!!!我放到是二叉树结点的地址,不是二叉树结点存的值
		QPush(&pq, root);
	}
	while (!QEmptyJudge(&pq))
	{
		BTNode* tmp = QFront(&pq);
		QPop(&pq);
		printf("%d ", tmp->data);  //这里打印的是二叉树结点的值
		if (tmp->left)
		{
			QPush(&pq, tmp->left); //这里存的是二叉树的左节点(不是值)
		}

		if (tmp->right)
		{
			QPush(&pq, tmp->right); //这里存的是二叉树的右节点(不是值)
		}
	}
	printf("\n");

	QDestroy(&pq);
}


////层序遍历 自己再实现一遍
//void LevelOrder(BTNode* root)
//{
//	Queue pq;
//	QInit(&pq);
//	if (root != NULL)
//	{
//		QPush(&pq,root);
//	}
//	while (!QEmptyJudge(&pq))
//	{
//		BTNode* front = QFront(&pq);
//		printf("%d ", front->data);
//		QPop(&pq);
//		if (root->left)
//			QPush(&pq, root->left);
//		if(root->right)
//			QPush(&pq, root->right);
//	}
//	printf("\n");
//
//	QDestroy(&pq);
//}



//判断二叉树是否是完全二叉树
bool BinaryTreeComplete(BTNode* root)
{
	Queue pq;
	QInit(&pq);
	if (root != NULL)
	{
		QPush(&pq, root);
	}
	while (!QEmptyJudge(&pq))
	{
		BTNode* front = QFront(&pq);
		QPop(&pq);

		if (front == NULL)
		{
			break;
		}
		QPush(&pq, front->left);
		QPush(&pq, front->right);
	}
	
	//遇到空以后,后面全是空,则是完全二叉树
	//遇到空以后,后面存在非空,则不是完全二叉树
	while (!QEmptyJudge(&pq))
	{
		BTNode* front = QFront(&pq);
		QPop(&pq);
		if (front != NULL)
		{
			QDestroy(&pq);
			return false;
		}
	}

	QDestroy(&pq);
	return true;
}


//二叉树销毁 - 后序遍历
void TreeDestroy(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}

	TreeDestroy(root->left);
	TreeDestroy(root->right);
	free(root);
}


BTNode* Test()
{
	BTNode* n1 = (BTNode*)malloc(sizeof(BTNode));
	BTNode* n2 = (BTNode*)malloc(sizeof(BTNode));
	BTNode* n3 = (BTNode*)malloc(sizeof(BTNode));
	BTNode* n4 = (BTNode*)malloc(sizeof(BTNode));
	BTNode* n5 = (BTNode*)malloc(sizeof(BTNode));
	BTNode* n6 = (BTNode*)malloc(sizeof(BTNode));
	BTNode* n7 = (BTNode*)malloc(sizeof(BTNode));
	BTNode* n8 = (BTNode*)malloc(sizeof(BTNode));

	n1->data = 1;
	n2->data = 2;
	n3->data = 3;
	n4->data = 4;
	n5->data = 5;
	n6->data = 6;
	n7->data = 7;
	n8->data = 8;

	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n3->left = n6;
	n3->right = n7;
	n4->left = n8;
	n4->right = NULL;
	n5->left = NULL;
	n5->right = NULL;
	n6->left = NULL;
	n6->right = NULL;
	n7->left = NULL;
	n7->right = NULL;
	n8->left = NULL;
	n8->right = NULL;

	return n1;
}

int main()
{
	BTNode* n1 = Test();
	LevelOrder(n1);
	printf("%d\n",BinaryTreeComplete(n1));
	//PreOrder(n1);
	//printf("\n");
	//InOrder(n1);
	//printf("\n");
	//PostOrder(n1);
	//printf("\n");
	//printf("%d\n", TreeSize(n1)); //8
	//printf("%d\n", LeafSize(n1)); //7
	//printf("%d\n", TreeHight(n1));//4
	//printf("%d\n", TreeKSize(n1, 4));//1
	//printf("%d\n", TreeKSize(n1, 3));//4
	//printf("%d\n", FindTreeNode(n1, 4)->data*10);//40

	//  1 2 4 8 5 3 6 7
	//	8 4 2 5 1 6 3 7
	//	8 4 5 2 6 7 3 1
	//	8
	//	7
	//	4
	//	1
	//  4
	//	40
	return 0;
}































