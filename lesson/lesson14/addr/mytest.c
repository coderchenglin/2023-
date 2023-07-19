#include<stdio.h>
#include<unistd.h>


int global_value = 100;

int main()
{
    pid_t id = fork();

    if(id < 0)
    {
        printf("fork error\n");
        return 1;
    }
    else if(id == 0)
    {
        int cnt = 0;
        while(1)
        {
            printf("我是子进程,pid : %d,ppid : %d | global_value : %d,  &global_value : %p\n",getpid(),getppid(),global_value,&global_value);
            sleep(1);
            cnt++;
            if(cnt == 10)
            {
                global_value = 300;
                printf("child changed\n");
            }
        }

        //printf("child\n");
    }
    else 
    {
        while(1)
        {
            printf("进程,pid : %d,ppid : %d | global_value : %d,  &global_value : %p\n",getpid(),getppid(),global_value,&global_value);
            sleep(1);
        }
        printf("father\n");
    }
    
    return 0;
}


