#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "program.h"

//整个程序的设计思路如下：
//
//定义了一个服装品牌的结构体 ClothingBrand，包含品牌名称和描述信息。
//定义了一个链表节点的结构体 Node，包含品牌信息和指向下一个节点的指针。
//在 main 函数中，首先加载数据文件（如果存在），然后显示菜单并接收用户的选项，根据用户的选项调用相应的函数。
//
//实现了各个功能函数，例如添加品牌、保存数据到文件、显示所有品牌、按名称和描述查询品牌、修改品牌信息、
//插入新品牌、删除品牌、统计品牌数量、对品牌进行排序、打印品牌报表等。
//
//在退出程序前，将数据保存到文件，并释放链表的内存。
//还有两个函数 encryptPassword 和 decryptPassword 用于密码的隐式输出、简单的加密和解密，但是需要根据具体需求来实现。


//定义一个结构体品牌结构
//定义链表结点结构
//定义链表头结点

//需要的函数功能实现:
//1.功能菜单函数
//2.添加品牌
//3.保存数据到文件
//4.显示所有文件
//5.搜索 - 搜索文件名
//6.搜索 - 按照文件描述
//7.更新品牌
//8.插入品牌 - 随机访问
//9.删除品牌
//10.输出品牌数量
//11.给品牌排序 - 按照名字
//12.打印报告
//13.加密密码
//14.解密密码



Node* head = NULL;  //定义一个头结点,初始化为NULL

//显示菜单
void displayMenu()
{
	printf("********** 服装品牌管理系统 **********\n");
	printf("1. 添加品牌\n");
	printf("2. 保存数据到文件\n");
	printf("3. 显示所有品牌\n");
	printf("4. 按名称查询品牌\n");
	printf("5. 按描述查询品牌\n");
	printf("6. 修改品牌信息\n");
	printf("7. 插入新品牌\n");
	printf("8. 删除品牌\n");
	printf("9. 统计品牌数量\n");
	printf("10. 对品牌进行排序\n");
	printf("11. 打印品牌报表\n");
	printf("0. 退出程序\n");
}

//添加品牌
void addBrand()
{
	ClothingBrand brand;

	printf("请输入品牌名称:\n");
	scanf("%s", brand.name);
	printf("请输入品牌描述:\n");
	scanf("%s", brand.description);

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->brand = brand;
	newNode->next = NULL;

	if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		Node* current = head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newNode;
	}

	printf("品牌添加成功!\n");
}

//将数据保存到文件
void saveDataToFile()
{
	//以写方式打开一个文件
	FILE* file = fopen(FILE_NAME, "w");
	//每次讲文件清空后,重新录入

	if (file == NULL)
	{
		printf("无法打开文件 %s.\n",FILE_NAME);
		return;
	}

	//从头遍历,将信息挨个录入文件
	Node* current = head;
	while (current != NULL)
	{
		fprintf(file, "%s;%s\n", current->brand.name, current->brand.description);
		current = current->next;
	}

	fclose(file);

	printf("数据保存成功 %s\n",FILE_NAME);
}

//从文件加载数据 - 读文件
void loadDataFromFile()
{
	//以只读方式打开文件
	FILE* file = fopen(FILE_NAME, "r");

	if (file == NULL)
	{
		printf("无法打开文件.\n");
		return;
	}

	char line[MAX_NAME_LENGTH + MAX_DESCRIPTION_LENGTH + 2];

	//fgets - 循环从文件中读取数据到缓冲区line中 并存入链表
	while (fgets(line, sizeof(line), file))
	{
		//把文件名和描述分隔开
		char* name = strtok(line, ";");
		char* description = strtok(NULL, "\n");

		Node* newNode = (Node*)malloc(sizeof(Node));
		strcpy(newNode->brand.name, name);
		strcpy(newNode->brand.description, description);
		newNode->next = NULL;

		//从头找打尾 然后链上
		if (head == NULL)
		{
			head = newNode;
		}
		else
		{
			Node* current = head;
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = newNode;
		}
	}

	fclose(file);

	printf("数据加载完毕!\n");
}

//显示所有品牌
void displayAllBrands()
{
	Node* current = head;

	if (current == NULL)
	{
		printf("没有任何品牌.\n");
	}

	while (current != NULL)
	{
		printf("名称: %s\n", current->brand.name);
		printf("描述: %s\n", current->brand.description);
		printf("-------------------------\n");
		current = current->next;
	}

}

//按名称查询品牌
void searchBrandByName()
{
	char name[MAX_NAME_LENGTH];

	printf("请输入要查询的品牌名称:");
	scanf("%s", name);

	Node* current = head;
	//标记
	//0 - 没找到
	//1 - 找到了
	int found = 0;

	while (current != NULL)
	{
		if (strcmp(current->brand.name, name) == 0)
		{
			printf("名称: %s\n", current->brand.name);
			printf("描述: %s\n", current->brand.description);
			printf("-------------------------\n");
			found = 1;
		}
	}

	if (!found)
	{
		printf("未找到匹配的品牌.\n");
	}
}

//按描述查询品牌
void searchBrandByDescription()
{
	char description[MAX_DESCRIPTION_LENGTH];

	printf("请输入要查询的品牌描述: ");
	scanf("%s", description);

	Node* current = head;
	int found = 0;

	while (current != NULL)
	{
		if (strcmp(current->brand.description, description) == 0)
		{
			printf("名称: %s\n", current->brand.name);
			printf("描述: %s\n", current->brand.description);
			printf("------------------------\n");
			found = 1;
		}

		current = current->next;
	}

	if (!found)
	{
		printf("未找到匹配的品牌.\n");
	}

}

//修改品牌信息
void updateBrand()
{
	char name[MAX_NAME_LENGTH];

	printf("请输入要修改的品牌名称:");
	scanf("%s", name);

	Node* current = head;
	int found = 0;

	while (current != NULL)
	{
		if (strcmp(current->brand.name,name) == 0)
		{
			printf("请输入新的品牌描述: ");
			scanf("%s", current->brand.description);
			printf("品牌信息已更新.\n");
			found = 1;
			break;
		}
		current = current->next;
	}

	if (!found)
	{
		printf("未找到匹配的品牌.\n");
	}

}

//插入新品牌
void insertBrand()
{
	int position;

	printf("请输入要插入的位置: ");
	scanf("%d", &position);


	//位置必须从0开始
	if (position < 1)
	{
		printf("无效的位置.\n");
		return;
	}

	ClothingBrand brand;

	printf("请输入品牌名称");
	scanf("%s", brand.name);
	printf("请输入品牌描述");
	scanf("%s", brand.description);

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->brand = brand;

	//头插
	if (position == 1)
	{
		newNode->next = head;
		head = newNode;
	}
	//中间(或尾)插入
	else
	{
		Node* current = head;
		int i = 1;
		while (current != NULL && i < position - 1)
		{
			current = current->next;
			i++;
		}

		if (current == NULL)
		{
			printf("无效的位置.\n");
			return;
		}
		//current newNode next
		newNode->next = current->next;
		current->next = newNode;
	}

	printf("品牌插入成功!\n");
}

//删除品牌
void deleteBrand()
{
	char name[MAX_NAME_LENGTH];

	printf("请输入要删除的品牌名称: ");
	scanf("%s", name);

	Node* current = head;
	Node* prev = NULL;
	int found = 0;

	while (current != NULL)
	{
		if (strcmp(current->brand.name, name) == 0)
		{
			//头删
			if (prev == NULL)
			{
				head = current->next;
			}
			//中间删除(尾删)
			else
			{
				prev->next = current->next;
			}
			free(current);
			printf("品牌已删除.\n");
			found = 1;
			break;
		}
		prev = current;
		current = current->next;
	}

	if (!found)
	{
		printf("未找到匹配的品牌.\n");
	}
}



//统计品牌数量
void countBrands()
{
	int count = 0;
	Node* current = head;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	printf("当前品牌数量: %d\n", count);
	
}

//对品牌进行排序 - 和链表排序有点不同
//这个只需要交换链表里的内容即可,不用改变链表结点的指向
void sortBrands()
{
	if (head == NULL || head->next == NULL)
	{
		printf("不需要要排序.\n");
		return;
	}

	int swapped;
	Node* current;
	Node* last = NULL;

	do {
		swapped = 0;
		current = head;
		
		while (current->next != last)
		{
			if (strcmp(current->brand.name, current->next->brand.name) > 0)
			{
				ClothingBrand temp = current->brand;
				current->brand = current->next->brand;
				current->next->brand = temp;
				swapped = 1;
			}

			current = current->next;
		}

		last = current;
	} while (swapped);

	printf("品牌排序完成!\n");
}

//打印品牌报表
void printReport()
{
	FILE* file = fopen("brand_report.txt", "w");

	if (file == NULL)
	{
		printf("无法打开文件.\n");
		return;
	}

	//fprintf函数是C语言中用于将格式化数据输出到文件的函数
	fprintf(file, "**************品牌报表****************\n");

	Node* current = head;
	while (current != NULL)
	{
		fprintf(file, "名称:%s\n", current->brand.name);
		fprintf(file, "描述:%s\n", current->brand.description);
		fprintf(file, "-----------------------------\n");
		current = current->next;
	}

	fclose(file);

	printf("品牌报表已打印.\n");
}

// 加密密码(简单替换加密)
void encryptPassword(char* password)
{
	int i = 0;
	while (password[i] != '\0')
	{
		password[i] = password[i] + 1;
		i++;
	}
}

//解密密码
void decryptPassword(char* password)
{
	int i = 0;

	while (password[i] != '/0')
	{
		password[i] = password[i] - 1;
		i++;
	}
}























