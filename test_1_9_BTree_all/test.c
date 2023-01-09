

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
//������������ʵ�ֵ�
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



//���г�ʼ��(������ĳ�ʼ��)
void QInit(Queue* pq)
{
	pq->head = pq->tail = NULL;
	pq->size = 0;
}

//����
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

	//���ﲻ��free(pq)
}


//���β(��������)
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

//�п�
bool QEmptyJudge(Queue* pq)
{
	return pq->tail == NULL;
}


//����ͷ
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


//��ͷԪ��
QueueDataType QFront(Queue* pq)
{
	assert(!QEmptyJudge(pq));
	return pq->head->data;
}


//��βԪ��
QueueDataType QBack(Queue* pq)
{
	assert(!QEmptyJudge(pq));
	return pq->tail->data;
}


//���д�С
int QSize(Queue* pq)
{
	return pq->size;
}


//----------------------


//������ǰ�����
void PreOrder(BTNode* root)
{
	if (root == NULL)
		return;

	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}


//�������������
void InOrder(BTNode* root)
{
	if (root == NULL)
		return;

	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);
}


// �������������
void PostOrder(BTNode* root)
{
	if (root == NULL)
		return;

	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
}


//����С
int TreeSize(BTNode* root)
{
	if (root == NULL)
		return 0;

	return TreeSize(root->left) + TreeSize(root->right) + 1;

}


//Ҷ����
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


//���߶�
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


//��k�������
int TreeKSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;

	if (k == 1)
		return 1;

	return TreeKSize(root->left, k - 1) + TreeKSize(root->right, k - 1);

}


//����x���ڵĽ��
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


//�����Ƿǵݹ�Ӧ��

//�������
void LevelOrder(BTNode* root)
{
	//����Ķ���!!
	//Queue* pq = NULL;
	//����:1.��ֱ�Ӷ���һ��ָ�����,û���ÿ�,����û�г�ʼ��,�ÿ�,��ַ��Ϊ��,Ϊ�յ�ָ�������ν�������?
	//     2.��ֻ���ȶ���һ���ṹ��,Ȼ��ȡ���ĵ�ַ,����������ַ������,���ܶ���
	//��ȷ�Ķ���:
	//Queue pq;
	Queue pq;
	QInit(&pq);
	if (root != NULL)
	{
		//ע��,��˼:������������ŵ��Ƕ�������ָ��!���Ƕ����������data!
		//��Ҫ����������!!!!!!!!!!!!�ҷŵ��Ƕ��������ĵ�ַ,���Ƕ����������ֵ
		QPush(&pq, root);
	}
	while (!QEmptyJudge(&pq))
	{
		BTNode* tmp = QFront(&pq);
		QPop(&pq);
		printf("%d ", tmp->data);  //�����ӡ���Ƕ���������ֵ
		if (tmp->left)
		{
			QPush(&pq, tmp->left); //�������Ƕ���������ڵ�(����ֵ)
		}

		if (tmp->right)
		{
			QPush(&pq, tmp->right); //�������Ƕ��������ҽڵ�(����ֵ)
		}
	}
	printf("\n");

	QDestroy(&pq);
}


////������� �Լ���ʵ��һ��
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



//�ж϶������Ƿ�����ȫ������
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
	
	//�������Ժ�,����ȫ�ǿ�,������ȫ������
	//�������Ժ�,������ڷǿ�,������ȫ������
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


//���������� - �������
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































