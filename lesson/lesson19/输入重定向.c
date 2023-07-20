#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


int main()
{
    umask(0);
    int fd = open("log.txt",O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        return 1;
    }

    dup2(fd,0);

    char line[64];

    while(1)
    {
        printf("> ");
        if(fgets(line,sizeof line,stdin) == NULL)
            break;
        printf("%s",line);
    }






    return 0;
}


