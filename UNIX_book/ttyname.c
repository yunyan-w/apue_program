#include<stdio.h>
#include<string.h>
#include<apue.h>
int main(void)
{
  char *name = NULL;
  for(int i=0;i<4;i++)
  {
    name = ttyname(i);
    if(isatty(i))
    {
      if(name != NULL)
      {
        printf("%d:%s\n",i,name);
      }
     
    }
    else
    {
       printf("not tty\n");  
    }
  }

}
