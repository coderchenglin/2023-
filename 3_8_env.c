 //这里用到了二级指针
 //environ 是系统定义好的一个二级指针,environ[i] = environ[]
 
 
 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<unistd.h>
 
 int main()
 {
      extern char **environ;                                                                               
     for(int i = 0;environ[i];i++)
     {
         printf("%d:%s\n",i,environ[i]);
     }
 
 
 
     return 0;
}
