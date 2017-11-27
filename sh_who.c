#include <stdio.h>
#include <sys/utsname.h>
#include <utmp.h>
#include "sh_who.h"

int get(void){
  struct utmp *n;
  setutent();
  n=getutent();

  while(n) {
    if(n->ut_type==USER_PROCESS) {
      printf("%3s%6s (%s)\n", n->ut_user, n->ut_line, n->ut_host);
    }
    n=getutent();
  }
  return 0;
}

int sh_who(char **args)
{
  get();
  return 1;
}