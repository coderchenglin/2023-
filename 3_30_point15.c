#include<stdio.h>

//用冒泡的思想,模拟实现一个系统调用函数qsort
//整个冒泡排序中,躺数确定,每一趟也确定,如何交换也确定(一个字节一个字节的换)
//唯一不确定的,只有如何比较两个元素大小
//因为待排序的元素类型不确定,所以比较两个元素类型的方法也不确定



//交换函数也是通用的
//难点:如何交换? 我不仅需要两个元素的地址,我还需要每个元素的大小
//因为我不知道要交换的元素的类型,所以我只能一个字节一个字节的进行交换,所以我需要一个元素的大小(宽度)
void Swap(char* buf1,char* buf2,int width)
{
    int i = 0;
    for(i = 0;i<width;i++)
    {
        char tmp = *buf1;
        *buf1 = *buf2;
        *buf2 = tmp;
        buf1++;
        buf2++;
    }
}

//实现一个qsort函数
void Bubble_sort(void* bath,size_t num,size_t size,int (*cmp)(const void* e1,const void* e2))
{
    int i = 0;
    for(i = 0;i<num-1;i++)
    {
        int j = 0;
        for(j = 0;j<num-1-i;j++)
        {
            //这里是一个难点:如何找到下标为j和j+1的元素的地址   :   j:  (char*)bath+j*size    j+1:   (char*)bath + (j+1)*size
            if(cmp((char*)bath+j*size,(char*)bath+(j+1)*size)>0)
            {
                Swap((char*)bath + j*size,(char*)bath + (j+1)*size,size);
            }
        }
    }
}




int main()
{
     



    return 0;
}





