#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

//文件的读和写,使用同一个偏移位置.
//先将内容写进文件,再讲文件的内容读出来时,记得先改变文件偏移量到文件起始位置,否则什么也读不到


int main()
{
    int fd,n;
    char msg[] = "It's a test for lseek\n";
    char ch;

    fd = open("lseek.txt",O_RDWR|O_CREAT,0644);
    if(fd < 0)
    {
        perror("open lseek.txt error");
        exit(1);
    }

    write(fd,msg,strlen(msg));
    lseek(fd,0,SEEK_SET);

    while((n = read(fd,&ch,1)))
    {
        if(n < 0)
        {
            perror("read error");
            exit(1);
        }
        else 
        {
            write(STDOUT_FILENO,&ch,1);
        }
    }

    close(fd);

    return 0;

}






