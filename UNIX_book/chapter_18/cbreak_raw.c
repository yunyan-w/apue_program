#define APUE_INCLUDE

#ifdef APUE_INCLUDE
#include<apue.h>
#else
#include<stdio.h>
#include<unistd.h>
#endif




static void sig_catch(int signo)
{
    printf("signal caught\n");
    tty_reset(STDIN_FILENO);
    exit(0);
}

void error_print(const char *s)
{
        #ifdef APUE_INCLUDE
        err_sys(s);
        #else
        printf("%s\n",s);
        #endif
}

int main(void)
{
    int i;
    char c;
    //  注册几个要关注的信号到函数ig_catch来处理
    if(signal(SIGINT,sig_catch) == SIG_ERR)
    {
        error_print("signal(SIGINT) error\n");    
    }
    if(signal(SIGQUIT,sig_catch) == SIG_ERR)
    {
        error_print("signal(SIGINT) error\n");    
    }
    if(signal(SIGTERM,sig_catch) == SIG_ERR)
    {
        error_print("signal(SIGINT) error\n");    
    }
    //  设置为raw模式
    if(tty_raw(STDIN_FILENO)) 
    {
        error_print("tty_raw error\n");    
    }
    printf("enter raw mode characters,terminate with DELETE\n");
    while( (i = read(STDIN_FILENO,&c,1)) == 1)  //  单字节读取到c中
    {
        if((c &= 255) == 0177)
        {
            break;
        }
        printf("%o\n",c);
    }
    if(tty_reset(STDIN_FILENO) < 0)  //  复位
    {
        error_print("tty_reset error\n");    
    }
    //  判断最后一次读是否正常
    if(i <= 0)
    {
        error_print("tty read error\n");    
    }
    if(tty_cbreak(STDIN_FILENO) < 0)
    {
        error_print("tty cbreak error\n");    
    }
    printf("Enter cbreak mode characters,terminate with SIGINT\n");
    while( (i = read(STDIN_FILENO,&c,1)) == 1) // 单字节读取
    {
        c &= 255;
        printf("%o\n",c);
    }
    if(tty_reset(STDIN_FILENO) < 0)
    {
        error_print("tty_reset error\n");    
    }
    if(i <= 0)
    {
        error_print("tty read error\n");    
    }
}

/*

 // STDIN_FILENO属于系统API接口库，其声明为 int 型，是一个打开文件句柄，对应的函数主要包括 open/read/write/close 等系统级调用。STDOUT_FILENO也是(一般分别为0,1)
    操作系统一级提供的文件API都是以文件描述符来表示文件。STDIN_FILENO就是标准输入设备（一般是键盘）的文件描述符。

*/


