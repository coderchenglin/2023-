#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int BTDataType;
typedef struct BinaryTreeNode
{
	BTDataType data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;

// ������ǰ�����
void PreOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}

	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}

// �������������
void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}

	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);
}

// �������������
void PostOrder(BTNode* root);

// ֪������
//int TreeSize(BTNode* root)
//{
//	static int count = 0;
//	if (root == NULL)
//		return count;
//
//	++count;
//	TreeSize(root->left);
//	TreeSize(root->right);
//
//	return count;
//}

// ��������
//int count = 0;
//void TreeSize(BTNode* root)
//{
//	if (root == NULL)
//		return;
//
//	++count;
//	TreeSize(root->left);
//	TreeSize(root->right);
//
//	return;
//}

// ������˼·���
int TreeSize(BTNode* root)
{
	return root == NULL ? 0 :
		TreeSize(root->left) + TreeSize(root->right) + 1;
}

int TreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;

	if (root->left == NULL
		&& root->right == NULL)
		return 1;

	return TreeLeafSize(root->left)
		+ TreeLeafSize(root->right);
}

int TreeHeight(BTNode* root)
{
	if (root == NULL)
		return 0;

	int lh = TreeHeight(root->left);
	int rh = TreeHeight(root->right);

	return lh > rh ? lh + 1 : rh + 1;
}

// ��K��ڵ����
int TreeKLevel(BTNode* root, int k)
{
	assert(k > 0);

	if (root == NULL)
		return 0;

	if (k == 1)
		return 1;

	// ת������������k-1��
	return TreeKLevel(root->left, k - 1)
		+ TreeKLevel(root->right, k - 1);
}

// ����x���ڵĽڵ�
BTNode* TreeFind(BTNode* root, BTDataType x)
{
	BTNode* lret, * rret;
	if (root == NULL)
		return NULL;

	if (root->data == x)
		return root;

	// ��ȥ������
	lret = TreeFind(root->left, x);
	if (lret)
		return lret;

	// ����û���ҵ����ٵ�������
	rret = TreeFind(root->right, x);
	if (rret)
		return rret;

	return NULL;
}

// ���Ƽ�
//BTNode* TreeFind(BTNode* root, BTDataType x)
//{
//	BTNode* lret;
//	if (root == NULL)
//		return NULL;
//
//	if (root->data == x)
//		return root;
//
//	// ��ȥ������
//	lret = TreeFind(root->left, x);
//	if (lret)
//		return lret;
//
//	return TreeFind(root->right, x);
//}

//BTNode* TreeFind(BTNode* root, BTDataType x)
//{
//	if (root == NULL)
//		return NULL;
//
//	if (root->data == x)
//		return root;
//
//	// ��ȥ������
//	struct BinaryTreeNode* lret = TreeFind(root->left, x);
//	if (lret)
//		return lret;
//
//	// ����û���ҵ����ٵ�������
//	struct BinaryTreeNode* rret = TreeFind(root->right, x);
//	if (rret)
//		return rret;
//
//	return NULL;
//}



BTNode* CreateTree()
{
	BTNode* n1 = (BTNode*)malloc(sizeof(BTNode));
	assert(n1);
	BTNode* n2 = (BTNode*)malloc(sizeof(BTNode));
	assert(n2);
	BTNode* n3 = (BTNode*)malloc(sizeof(BTNode));
	assert(n3);
	BTNode* n4 = (BTNode*)malloc(sizeof(BTNode));
	assert(n4);
	BTNode* n5 = (BTNode*)malloc(sizeof(BTNode));
	assert(n5);
	BTNode* n6 = (BTNode*)malloc(sizeof(BTNode));
	assert(n6);
	BTNode* n7 = (BTNode*)malloc(sizeof(BTNode));
	assert(n7);

	n1->data = 1;
	n2->data = 2;
	n3->data = 3;
	n4->data = 4;
	n5->data = 5;
	n6->data = 6;
	n7->data = 7;

	n1->left = n2;
	n1->right = n4;
	n2->left = n3;
	n2->right = NULL;
	n4->left = n5;
	n4->right = n6;
	n3->left = NULL;
	n3->right = NULL;
	n5->left = NULL;
	n5->right = NULL;
	n6->left = NULL;
	n6->right = NULL;

	n3->right = n7;
	n7->left = NULL;
	n7->right = NULL;

	return n1;
}

int main()
{
	BTNode* root = CreateTree();
	PreOrder(root);
	printf("\n");

	InOrder(root);
	printf("\n");

	//count = 0;
	//TreeSize(root);
	//printf("Tree size:%d\n", count);

	//count = 0;
	//TreeSize(root);
	//printf("Tree size:%d\n", count);

	printf("Tree size:%d\n", TreeSize(root));
	printf("Tree size:%d\n", TreeSize(root));
	printf("Tree size:%d\n", TreeSize(root));

	printf("Tree Leaf size:%d\n", TreeLeafSize(root));
	printf("Tree Height:%d\n", TreeHeight(root));
	printf("Tree K Level:%d\n", TreeKLevel(root, 3));
	printf("Tree Find:%p\n", TreeFind(root, 8));

	BTNode* ret = TreeFind(root, 7);
	ret->data *= 10;

	PreOrder(root);
	printf("\n");

	return 0;
}