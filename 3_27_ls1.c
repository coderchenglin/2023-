#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<dirent.h>
#include<errno.h>

//这个demo可以练习一下,目录操作函数
//DIR* dp;
//struct dirent* sdp;
//dp = opendir(path)
//sdp = readdir(dp)
//closedir(dp);

//struct dirent{
//   inode
//   char name[256];
//}


int main(int argc,char* argv[])
{
    DIR* dp;  //目录描述符
    struct dirent* sdp;  //目录项结构体

    dp = opendir(argv[1]);
    if(dp == NULL)
    {
        perror("opendir error");
        exit(1);
    }

    while((sdp = readdir(dp)) != NULL)   //一次只能读出一个目录项
    {
        //隐藏"." 个".."
        if((strcmp(sdp->d_name,".")==0||strcmp(sdp->d_name,"..")==0))
        {
            continue;
        }
    
        printf("%s\t",sdp->d_name);
    }
    printf("\n");

    closedir(dp);
        
    return 0;
}

