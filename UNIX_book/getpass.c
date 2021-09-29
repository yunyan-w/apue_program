
#ifdef APUE_INCLUDE
#include <apue.h>
#else
#include<stdio.h>
#include<unistd.h>
#endif
char *getpass(const char *);//  声明
int main(void)
{
    char *ptr;
    printf("%d,%d",STDIN_FILENO,STDOUT_FILENO);
    if( (ptr = getpass("Enter paword:")) == NULL)
    {
        #ifdef APUE_INCLUDE
        err_sys("getpass error");
        #else
        return 0;
        #endif
    }   
    printf("password:%s \n",ptr);
    while(*ptr != 0)  //  为了安全起见，子程序完成后应当在内存中清除它。
    {
        *ptr++ = 0;
    }
}
