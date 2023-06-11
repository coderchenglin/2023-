#define _CRT_SECURE_NO_WARNINGS

#pragma once


#define MAX_NAME_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 100
#define FILE_NAME "clothing_data.txt"

// �����װƷ�ƽṹ
typedef struct
{
	char name[MAX_NAME_LENGTH];
	char description[MAX_DESCRIPTION_LENGTH];
}ClothingBrand;

//����������ṹ
typedef struct Node
{
	ClothingBrand brand;
	struct Node* next;
}Node;



// ��������
void displayMenu();
void addBrand();
void saveDataToFile();
void loadDataFromFile();
void displayAllBrands();
void searchBrandByName();
void searchBrandByDescription();
void updateBrand();
void insertBrand();
void deleteBrand();
void countBrands();
void sortBrands();
void printReport();
void encryptPassword(char* password);
void decryptPassword(char* password);