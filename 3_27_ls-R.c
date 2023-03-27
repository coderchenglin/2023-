#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/stat.h>
#include<dirent.h>
#include<sys/types.h>


void isFile(char* name);

void read_dir(char* dir)
{
    char path[256];
    DIR* dp;
    struct dirent* sdp;

    dp = opendir(dir);
    if(dp == NULL)
    {
        perror("opendir error");
        return;
    }
    
    while((sdp = readdir(dp)) != NULL)
    {
       // 读到了目录项以后1.判断这个目录项是文件还是目录
       // 如果还是目录,继续进去,如果是文件,直接打印
       // 文件打印是isFILE函数的功能
       //错误写法:readdir(sdp->d_name)  //我们需要拼接出绝对路径
       //字符串拼接除了用strcat函数外,还有一个更简单的函数,sprintf(path,"%s\%s",name,sdp->d_name);
      
      //如果不排除.和..的情况,会出现无限死循环递归的情况

        if(strcmp(sdp->d_name,".")==0 || strcmp(sdp->d_name,"..") == 0)
            continue;

        sprintf(path,"%s/%s",dir,sdp->d_name);  
        isFile(path);
    
    }
    closedir(dp);

    return;
}

void isFile(char* name)
{
    int ret = 0;
    struct stat sb;   //stat buf

    ret = stat(name,&sb);  //sb是个传出参数
    if(ret == -1)
    {
        perror("stat error");
        return;
    }

    if(S_ISDIR(sb.st_mode))
    {
        read_dir(name);   
    }

    printf("%20s\t%ld\n",name,sb.st_size);

    return;
}

int main(int argc,char* argv[])
{
    if(argc == 1)   //ls 后面没有接参数
    {
        isFile(".");
    }
    else 
    {
        isFile(argv[1]);
    }

    return 0;
}








