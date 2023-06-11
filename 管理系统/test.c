#define _CRT_SECURE_NO_WARNINGS
#include "program.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	Node* head = NULL;
	int choice;
	char password[20];

	printf("请输入密码: ");
	scanf("%s", password);

	//decryptPassword(password);  // 解密密码

	if (strcmp(password, "12345678") != 0)
	{
		printf("密码错误,程序退出!\n");
		return 0;
	}

	loadDataFromFile(); //从文件加载数据

	do {
		displayMenu();
		printf("请输入选项:");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			addBrand();
			break;
		case 2:
			saveDataToFile();
			break;
		 case 3:
			displayAllBrands();
			break;
		case 4:
			searchBrandByName();
			break;
		case 5:
			searchBrandByDescription();
			break;
		case 6:
			updateBrand();
			break;
		case 7:
			insertBrand();
			break;
		case 8:
			deleteBrand();
			break;
		case 9:
			countBrands();
			break;
		case 10:
			sortBrands();
			break;
		case 11:
			printReport();
			break;
		case 0:
			printf("程序已退出.\n");
			break;
		default:
			printf("无效的选项,请重新输入.\n");
		}

		printf("\n");

	} while (choice != 0); // 只要输入不等于0,就继续

	Node* current = head;
	while (current != NULL) {
		Node* temp = current;
		current = current->next;
		free(temp);
	}

	return 0;
}