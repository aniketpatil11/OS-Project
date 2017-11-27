#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<unistd.h>
#include "sh_ls.h"
int sh_ls(char **args)
{
char dirname[1000];
DIR*p;
struct dirent *d;
getcwd(dirname,sizeof(dirname));
p=opendir(dirname);
if(p==NULL)
  {
  perror("Cannot find directory");
  exit(-1);
  }
while(d=readdir(p))
  printf("%s\n",d->d_name);
return 1;
}