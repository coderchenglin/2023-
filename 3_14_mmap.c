#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>  // open
#include<sys/mman.h>


void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    char* p = NULL;
    int fd;

    fd = open("testmap",O_RDWR|O_CREAT|O_TRUNC,0644);
    if(fd == -1)
    {
        sys_err("open error");
    }

    //拓展文件大小  --  拓展出来的文件尾21字节  --  下面两种方式等价
/*
    lseek(fd,20,SEEK_END);
    write(fd,"\0",1);
*/
    ftruncate(fd,20);  //和上面两行代码功能一样
    int len = lseek(fd,0,SEEK_END);

    p = (char*)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);  //返回值为共享映射区的首地址
    if(p == MAP_FAILED)
    {
        sys_err("mmap error");
    }

    //使用p对文件进行读写操作
    strcpy(p,"hello mmap");

    printf("----%s\n",p);

    int ret = munmap(p,len);   //释放映射区
    if(ret == -1)
    {
        sys_err("munmap error");
    }
    
    close(fd);


    return 0;
}





//int munmap(void *addr,size_t length);    释放映射区
//返回值:常规返回0,失败返回-1



/*
使用注意事项:
    1.用于创建映射区的文件大小0,实际指定非0大小创建映射区,出"总线错误";
    2.用于创建映射区的文件大小0,实际指定0大小创建映射区,出"无效参数";
    3.用于创建映射区的文件读写属性为,只读.映射区属性为,读,写.出"无效参数";
    4.创建映射区,需要 读权限 .因此,mmap的读写权限,应该<=文件的open权限.
    5.文件描述符fd,在mmap创建映射区完成后,即可关闭了.因为后面方位那块映射区,用地址访问.
    6.offset参数(最后一个参数),必须是4k(即4096)的整数倍,因为最小单位就是4k.
    7.对申请的映射区内存,不能越界访问
    8.munmap用于释放的地址,必须是map
    9.mmap函数的返回值必须要进行检查,因为很容易出错


*/









