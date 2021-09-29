/*必要头文件包含*/
#define APUE_INCLUDE
#ifdef APUE_INCLUDE
#include<apue.h>
#else
#include<stdio.h>
#include<unistd.h>
#include <signal.h>		/* for SIG_ERR */
#endif

#include<termios.h>
#include <time.h>
//  错误判断
#include <errno.h>
#ifndef TIOCGWINSZ
#include<sys/ioctl.h>
#endif

/*函数声明*/
void error_print(const char *s);
static void pr_winsize(int fd);
static void sig_winch(int signo);
int msleep(long msec);

/*主函数*/
int main(void)
{
    //  检查是否是终端
    if(isatty(STDIN_FILENO) == 0)
    {
        return 0;
    }
    //  注册信号
    if( signal(SIGWINCH,sig_winch) == SIG_ERR )
    {
        error_print("signal error");
    }
    //  打印当前终端窗口大小
    pr_winsize(STDIN_FILENO);
    while (1)
    {
        msleep(10);
    }
    //pause();  // 暂停直到下一个信号到来
    
}




/***********************************************************
* @从属类 无
* @函数名 sig_winch
* @函数功能  信号处理函数,负责捕获信号并调用以pr_winsize打印窗口大小
* @输入参数   给入的信号值
* @返回参数 无
* @补充     
*************************************************************/
static void sig_winch(int signo)
{
    printf("SIGWINCH received \n");
    pr_winsize(STDIN_FILENO);
}


/***********************************************************
* @从属类 无
* @函数名 pr_winsize
* @函数功能  打印给定终端的窗口大小
* @输入参数    file descriptor
* @返回参数 
* @补充     
*************************************************************/
static void pr_winsize(int fd)
{
    struct winsize size;
    if( ioctl(fd,TIOCGWINSZ,(char *) &size) < 0 ) //  获得当前窗口大小
    {
        error_print("TIOCGWINSZ error");
    }
    printf("%d rows,%d columns \n",size.ws_row,size.ws_col);//  显示当前窗口大小
    if( ioctl(fd,TIOCSWINSZ,(char *) &size) < 0 ) //  获得当前窗口大小
    {
        error_print("TIOCSWINSZ error");
    }
}

/*消息打印*/
/***********************************************************
* @从属类 无
* @函数名 error_print
* @函数功能 打印错误信息
* @输入参数  信息字符串指针
* @返回参数 
* @补充     
*************************************************************/
void error_print(const char *s)
{
        //#ifdef APUE_INCLUDE
        //err_sys(s);
        //#else
        printf("%s\n",s);
        //#endif
}


/***********************************************************
* @从属类 无
* @函数名 msleep
* @函数功能 休眠
* @输入参数  时间(ms)
* @返回参数 
* @补充     
*************************************************************/
int msleep(long msec)
{
    struct timespec ts;
    int res;
    if (msec < 0)
    {
        return -1;
    }
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do 
    {
        res = nanosleep(&ts, &ts);
    } 
    while (res && errno == EINTR);

    return res;
}