#include <stdio.h>
#include <string.h>

int main(void)
{
  char ctermid_name[L_ctermid];
  char *ptr = ctermid(NULL);
  if(ptr !=NULL)
  {
    printf("%s\n",ptr);
  }

}
