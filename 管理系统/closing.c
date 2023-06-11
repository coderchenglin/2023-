#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "program.h"

//������������˼·���£�
//
//������һ����װƷ�ƵĽṹ�� ClothingBrand������Ʒ�����ƺ�������Ϣ��
//������һ������ڵ�Ľṹ�� Node������Ʒ����Ϣ��ָ����һ���ڵ��ָ�롣
//�� main �����У����ȼ��������ļ���������ڣ���Ȼ����ʾ�˵��������û���ѡ������û���ѡ�������Ӧ�ĺ�����
//
//ʵ���˸������ܺ������������Ʒ�ơ��������ݵ��ļ�����ʾ����Ʒ�ơ������ƺ�������ѯƷ�ơ��޸�Ʒ����Ϣ��
//������Ʒ�ơ�ɾ��Ʒ�ơ�ͳ��Ʒ����������Ʒ�ƽ������򡢴�ӡƷ�Ʊ���ȡ�
//
//���˳�����ǰ�������ݱ��浽�ļ������ͷ�������ڴ档
//������������ encryptPassword �� decryptPassword �����������ʽ������򵥵ļ��ܺͽ��ܣ�������Ҫ���ݾ���������ʵ�֡�


//����һ���ṹ��Ʒ�ƽṹ
//����������ṹ
//��������ͷ���

//��Ҫ�ĺ�������ʵ��:
//1.���ܲ˵�����
//2.���Ʒ��
//3.�������ݵ��ļ�
//4.��ʾ�����ļ�
//5.���� - �����ļ���
//6.���� - �����ļ�����
//7.����Ʒ��
//8.����Ʒ�� - �������
//9.ɾ��Ʒ��
//10.���Ʒ������
//11.��Ʒ������ - ��������
//12.��ӡ����
//13.��������
//14.��������



Node* head = NULL;  //����һ��ͷ���,��ʼ��ΪNULL

//��ʾ�˵�
void displayMenu()
{
	printf("********** ��װƷ�ƹ���ϵͳ **********\n");
	printf("1. ���Ʒ��\n");
	printf("2. �������ݵ��ļ�\n");
	printf("3. ��ʾ����Ʒ��\n");
	printf("4. �����Ʋ�ѯƷ��\n");
	printf("5. ��������ѯƷ��\n");
	printf("6. �޸�Ʒ����Ϣ\n");
	printf("7. ������Ʒ��\n");
	printf("8. ɾ��Ʒ��\n");
	printf("9. ͳ��Ʒ������\n");
	printf("10. ��Ʒ�ƽ�������\n");
	printf("11. ��ӡƷ�Ʊ���\n");
	printf("0. �˳�����\n");
}

//���Ʒ��
void addBrand()
{
	ClothingBrand brand;

	printf("������Ʒ������:\n");
	scanf("%s", brand.name);
	printf("������Ʒ������:\n");
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

	printf("Ʒ����ӳɹ�!\n");
}

//�����ݱ��浽�ļ�
void saveDataToFile()
{
	//��д��ʽ��һ���ļ�
	FILE* file = fopen(FILE_NAME, "w");
	//ÿ�ν��ļ���պ�,����¼��

	if (file == NULL)
	{
		printf("�޷����ļ� %s.\n",FILE_NAME);
		return;
	}

	//��ͷ����,����Ϣ����¼���ļ�
	Node* current = head;
	while (current != NULL)
	{
		fprintf(file, "%s;%s\n", current->brand.name, current->brand.description);
		current = current->next;
	}

	fclose(file);

	printf("���ݱ���ɹ� %s\n",FILE_NAME);
}

//���ļ��������� - ���ļ�
void loadDataFromFile()
{
	//��ֻ����ʽ���ļ�
	FILE* file = fopen(FILE_NAME, "r");

	if (file == NULL)
	{
		printf("�޷����ļ�.\n");
		return;
	}

	char line[MAX_NAME_LENGTH + MAX_DESCRIPTION_LENGTH + 2];

	//fgets - ѭ�����ļ��ж�ȡ���ݵ�������line�� ����������
	while (fgets(line, sizeof(line), file))
	{
		//���ļ����������ָ���
		char* name = strtok(line, ";");
		char* description = strtok(NULL, "\n");

		Node* newNode = (Node*)malloc(sizeof(Node));
		strcpy(newNode->brand.name, name);
		strcpy(newNode->brand.description, description);
		newNode->next = NULL;

		//��ͷ�Ҵ�β Ȼ������
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

	printf("���ݼ������!\n");
}

//��ʾ����Ʒ��
void displayAllBrands()
{
	Node* current = head;

	if (current == NULL)
	{
		printf("û���κ�Ʒ��.\n");
	}

	while (current != NULL)
	{
		printf("����: %s\n", current->brand.name);
		printf("����: %s\n", current->brand.description);
		printf("-------------------------\n");
		current = current->next;
	}

}

//�����Ʋ�ѯƷ��
void searchBrandByName()
{
	char name[MAX_NAME_LENGTH];

	printf("������Ҫ��ѯ��Ʒ������:");
	scanf("%s", name);

	Node* current = head;
	//���
	//0 - û�ҵ�
	//1 - �ҵ���
	int found = 0;

	while (current != NULL)
	{
		if (strcmp(current->brand.name, name) == 0)
		{
			printf("����: %s\n", current->brand.name);
			printf("����: %s\n", current->brand.description);
			printf("-------------------------\n");
			found = 1;
		}
	}

	if (!found)
	{
		printf("δ�ҵ�ƥ���Ʒ��.\n");
	}
}

//��������ѯƷ��
void searchBrandByDescription()
{
	char description[MAX_DESCRIPTION_LENGTH];

	printf("������Ҫ��ѯ��Ʒ������: ");
	scanf("%s", description);

	Node* current = head;
	int found = 0;

	while (current != NULL)
	{
		if (strcmp(current->brand.description, description) == 0)
		{
			printf("����: %s\n", current->brand.name);
			printf("����: %s\n", current->brand.description);
			printf("------------------------\n");
			found = 1;
		}

		current = current->next;
	}

	if (!found)
	{
		printf("δ�ҵ�ƥ���Ʒ��.\n");
	}

}

//�޸�Ʒ����Ϣ
void updateBrand()
{
	char name[MAX_NAME_LENGTH];

	printf("������Ҫ�޸ĵ�Ʒ������:");
	scanf("%s", name);

	Node* current = head;
	int found = 0;

	while (current != NULL)
	{
		if (strcmp(current->brand.name,name) == 0)
		{
			printf("�������µ�Ʒ������: ");
			scanf("%s", current->brand.description);
			printf("Ʒ����Ϣ�Ѹ���.\n");
			found = 1;
			break;
		}
		current = current->next;
	}

	if (!found)
	{
		printf("δ�ҵ�ƥ���Ʒ��.\n");
	}

}

//������Ʒ��
void insertBrand()
{
	int position;

	printf("������Ҫ�����λ��: ");
	scanf("%d", &position);


	//λ�ñ����0��ʼ
	if (position < 1)
	{
		printf("��Ч��λ��.\n");
		return;
	}

	ClothingBrand brand;

	printf("������Ʒ������");
	scanf("%s", brand.name);
	printf("������Ʒ������");
	scanf("%s", brand.description);

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->brand = brand;

	//ͷ��
	if (position == 1)
	{
		newNode->next = head;
		head = newNode;
	}
	//�м�(��β)����
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
			printf("��Ч��λ��.\n");
			return;
		}
		//current newNode next
		newNode->next = current->next;
		current->next = newNode;
	}

	printf("Ʒ�Ʋ���ɹ�!\n");
}

//ɾ��Ʒ��
void deleteBrand()
{
	char name[MAX_NAME_LENGTH];

	printf("������Ҫɾ����Ʒ������: ");
	scanf("%s", name);

	Node* current = head;
	Node* prev = NULL;
	int found = 0;

	while (current != NULL)
	{
		if (strcmp(current->brand.name, name) == 0)
		{
			//ͷɾ
			if (prev == NULL)
			{
				head = current->next;
			}
			//�м�ɾ��(βɾ)
			else
			{
				prev->next = current->next;
			}
			free(current);
			printf("Ʒ����ɾ��.\n");
			found = 1;
			break;
		}
		prev = current;
		current = current->next;
	}

	if (!found)
	{
		printf("δ�ҵ�ƥ���Ʒ��.\n");
	}
}



//ͳ��Ʒ������
void countBrands()
{
	int count = 0;
	Node* current = head;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	printf("��ǰƷ������: %d\n", count);
	
}

//��Ʒ�ƽ������� - �����������е㲻ͬ
//���ֻ��Ҫ��������������ݼ���,���øı��������ָ��
void sortBrands()
{
	if (head == NULL || head->next == NULL)
	{
		printf("����ҪҪ����.\n");
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

	printf("Ʒ���������!\n");
}

//��ӡƷ�Ʊ���
void printReport()
{
	FILE* file = fopen("brand_report.txt", "w");

	if (file == NULL)
	{
		printf("�޷����ļ�.\n");
		return;
	}

	//fprintf������C���������ڽ���ʽ������������ļ��ĺ���
	fprintf(file, "**************Ʒ�Ʊ���****************\n");

	Node* current = head;
	while (current != NULL)
	{
		fprintf(file, "����:%s\n", current->brand.name);
		fprintf(file, "����:%s\n", current->brand.description);
		fprintf(file, "-----------------------------\n");
		current = current->next;
	}

	fclose(file);

	printf("Ʒ�Ʊ����Ѵ�ӡ.\n");
}

// ��������(���滻����)
void encryptPassword(char* password)
{
	int i = 0;
	while (password[i] != '\0')
	{
		password[i] = password[i] + 1;
		i++;
	}
}

//��������
void decryptPassword(char* password)
{
	int i = 0;

	while (password[i] != '/0')
	{
		password[i] = password[i] - 1;
		i++;
	}
}























