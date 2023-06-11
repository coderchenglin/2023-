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

	printf("����������: ");
	scanf("%s", password);

	//decryptPassword(password);  // ��������

	if (strcmp(password, "12345678") != 0)
	{
		printf("�������,�����˳�!\n");
		return 0;
	}

	loadDataFromFile(); //���ļ���������

	do {
		displayMenu();
		printf("������ѡ��:");
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
			printf("�������˳�.\n");
			break;
		default:
			printf("��Ч��ѡ��,����������.\n");
		}

		printf("\n");

	} while (choice != 0); // ֻҪ���벻����0,�ͼ���

	Node* current = head;
	while (current != NULL) {
		Node* temp = current;
		current = current->next;
		free(temp);
	}

	return 0;
}