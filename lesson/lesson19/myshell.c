#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<assert.h>

#include<ctype.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>



#define NUM 1024
#define OPT_NUM 64

#define NONE_REDIR  0
#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3

//宏函数
#define trimSpace(start) do{ \
    while(isspace(*start)) \
    ++start; \
}while(0)




char lineCommand[NUM];
char *myargv[OPT_NUM];   //指针数组
int lastCode = 0;
int lastSig = 0;

//定义全局变量,用来保存重定向类型和文件名
int redirType = NONE_REDIR;
char* redirFile = NULL;

//命令解析
void commandCheck(char* commands)
{
    assert(commands);
    char* start = commands;
    char* end = commands + strlen(commands);

    while(start < end)
    {
        if(*start == '>')
        {
            *start = '\0';
            start++;
            if(*start == '>')
            {
                // "ls -a >> file.log"
                redirType = APPEND_REDIR; //追加重定向
                start++;
            }
            else 
            {
                // "ls -a >   file.log"
                redirType = OUTPUT_REDIR;
            }
            trimSpace(start);
            redirFile = start;
            break;
        }
        else if(*start == '<')
        {
            // "cat <    file.txt"
            *start = '\0';
            start++;
            trimSpace(start);
            //填写重定向信息
            redirType = INPUT_REDIR;
            redirFile = start;
            break;
        }
        else 
        {
            start++;
        }
    }


}


int main()
{
    while(1)
    {
        //每一次都需要初始化重定向信息
        redirType = NONE_REDIR;
        redirFile = NULL; 
        errno = 0;


        //输出提示符
        printf("用书名@主机名 当前路径#");
        fflush(stdout);
        
        //获取用户输入,输入的时候,输入\n 
        char* s = fgets(lineCommand,sizeof(lineCommand)-1,stdin);
        assert(s != NULL);
        (void)s;
    
        //清除最后一个\n,abcd\n
        lineCommand[strlen(lineCommand)-1] = 0;

        commandCheck(lineCommand);
        //字符串切割
        myargv[0] = strtok(lineCommand," ");

        //如果没有子串了,strtok->NULL myargv[end] = NULL 
        int i = 1;
        if(myargv[0] != NULL && strcmp(myargv[0],"ls") == 0)
        {
            myargv[i++] = (char*)"--color=auto";
        }

        //如果没有子串了,strtok->NULL myargv[end] = NULL 
        while(myargv[i++] = strtok(NULL," "));

        //如果是cd命令,不需要创建子进程,让shell自己执行对应的命令,本质就是执行系统接口
        //像这种不需要让我们的子进程来执行,而是让shell自己执行的命令 -- 内建/内置命令
        if(myargv[0] != NULL && strcmp(myargv[0],"cd") == 0)
        {
            if(myargv[1] != NULL)
                chdir(myargv[1]);
            continue;
        }
        if(myargv[0] != NULL && myargv[1] != NULL && strcmp(myargv[0],"echo") == 0)
        {
            if(strcmp(myargv[1],"$?") == 0)
            {
                printf("%d,%d\n",lastCode,lastSig);  // 打印退出码 和 信号量
            }
            else 
            {
                printf("%s\n",myargv[1]);
            }
            continue;
        }

#ifdef DEBUG 
        for(int i = 0;myargv[i];i++)
        {
         printf("myargv[%d]:%s\n",i,myargv[i]);
        }
#endif 

        //内建命令 --> echo
        

        //执行命令
        pid_t id = fork();
        assert(id != -1);

        if(id == 0)
        {
            //因为命令是子进程执行的,真正重定向的工作一定要子进程来完成
            //如何重定向,是父进程要给子进程提供信息的
            //这里重定向 不会硬父进程! 因为,进程具有独立性
            switch(redirType)
            {
                case NONE_REDIR:
                    //什么都不做
                    break;
                case INPUT_REDIR:
                    {
                        int fd = open(redirFile,O_RDONLY);
                        if(fd < 0)
                        {
                            perror("open");
                            exit(errno);
                        }
                        dup2(fd,0);
                    }
                    break;
                case OUTPUT_REDIR:
                case APPEND_REDIR:
                    {
                        umask(0);
                        int flags = O_WRONLY | O_CREAT;
                        if(redirType == APPEND_REDIR) 
                            flags |= O_APPEND;
                        else 
                            flags |= O_TRUNC;
                        int fd = open(redirFile,flags,0666);
                        if(fd < 0)
                        {
                            perror("open");
                            exit(errno);
                        }
                        dup2(fd,1);

                    }
                    break;
                default:
                    printf("bug\n");
                    break;
            }

            execvp(myargv[0],myargv);
            exit(1);
        }
        int status = 0;
        pid_t ret = waitpid(id,&status,0);
        assert(ret > 0);
        (void)ret;  //表示我们不关心这个函数的返回值
        lastCode = ((status>>8) & 0xFF);
        lastSig = (status & 0x7F);
    }
    return 0;
}





