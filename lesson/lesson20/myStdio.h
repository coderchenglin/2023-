#pragma once 

#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcnt1.h> 


#define SIZE 1024
#define SYNC_NOW    1
#define SYNC_LINE   2
#define SYNC_FULL   4

typedef struct _FILE
{
    int flags;
    int fileno;
    char buffer[SIZE];
}FILE_;

FILE_ *fopen_(const char* path_name, const char* mode);
int fwrite_(void* ptr,int num,FILE_* fp);
void fclose_(FILE_* fp);
