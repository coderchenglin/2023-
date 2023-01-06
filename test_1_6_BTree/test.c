
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef struct BinaryTree
{
	struct BinaryTree* left;
	struct BinaryTree* right;
	int data;
}BT;



//二叉树前序遍历
void PreOrder(BT* pb)
{
	if (pb == NULL)
	{
		return;
	}

	printf("%d", pb->data);
	PreOrder(pb->left);
	PreOrder(pb->right);
}

//二叉树中序遍历
void InOrder(BT* pb)
{
	if (pb == NULL)
	{
		return;
	}

	InOrder(pb->left);
	printf("%d", pb->data);
	InOrder(pb->right);
}

//二叉树后序遍历
void PostOrder(BT* pb)
{
	if (pb == NULL)
	{
		return;
	}

	PostOrder(pb->left);
	PostOrder(pb->right);
	printf("%d", pb->data);
}

//遍历计数
int TreeSize(BT* pb)
{
	if (pb == NULL)
		return 0;

	return TreeSize(pb->left) + TreeSize(pb->right) + 1;
}

//子问题思路解决
//1.求树的大小
int TreeSize(BT* pb);

//2.求叶子结点的个数
int LeafSize(BT* pb)
{
	if (pb == NULL)
		return 0;

	if (pb->left == NULL && pb->right == NULL)
		return 1;

	return LeafSize(pb->left) + LeafSize(pb->right);
}

//3.求树的高度
int TreeHight(BT* pb)
{
	if (pb == NULL)
		return 0;

	int lret = TreeHight(pb->left);
	int rret = TreeHight(pb->right);

	return lret > rret ? lret + 1 : rret + 1;

}

//4.第k层结点个数
int KSize(BT* pb, int k)
{
	if (pb == NULL)
		return 0;

	if (k == 0)
		return 1;

	return KSize(pb->left, k - 1) + KSize(pb->right, k - 1);
}

//5.找节点:返回x所在的节点地址
BT* FindX(BT* pb, int x)
{
	if (pb == NULL)
		return NULL;
	if (pb->data == x)
		return pb;
	BT* lret = FindX(pb->left, x);
	if (lret)
		return lret;
	BT* rret = FindX(pb->right, x);
	if (rret)
		return rret;

	return NULL;
}



int main()
{
	BT* n1 = (BT*)malloc(sizeof(BT));
	BT* n2 = (BT*)malloc(sizeof(BT));
	BT* n3 = (BT*)malloc(sizeof(BT));
	BT* n4 = (BT*)malloc(sizeof(BT));
	BT* n5 = (BT*)malloc(sizeof(BT));
	BT* n6 = (BT*)malloc(sizeof(BT));
	BT* n7 = (BT*)malloc(sizeof(BT));

	n1->data = 1;
	n2->data = 2;
	n3->data = 3;
	n4->data = 4;
	n5->data = 5;
	n6->data = 6;
	n7->data = 7;

	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n3->left = n6;
	n3->right = n7;
	n4->left = NULL;
	n4->right = NULL;
	n5->left = NULL;
	n5->right = NULL;
	n6->left = NULL;
	n6->right = NULL;
	n7->left = NULL;
	n7->right = NULL;

	//PreOrder(n1);
	//printf("\n");
	//printf("TreeSize:%d\n", TreeSize(n1));
	//printf("LeafSize:%d\n", LeafSize(n1));
	//printf("TreeHight:%d\n", TreeHight(n1));
	//printf("KSize:%d\n", KSize(n1, 0));
	//printf("KSize:%d\n", KSize(n1, 1));
	//printf("KSize:%d\n", KSize(n1, 2));
	//printf("KSize:%d\n", KSize(n1, 3));
	//printf("KSize:%d\n", KSize(n1, 4));
	BT* tmp = FindX(n1, 4);
	printf("%d", FindX(n1, 4)->data);
	

	return 0;
}