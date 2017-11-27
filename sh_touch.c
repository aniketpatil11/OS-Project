#include <stdio.h>
#include <string.h>
#include "sh_touch.h"
int  sh_touch(char **args)
{
	FILE *fp;
	char fline[100];
	char *newline;
	int i,count=0,occ=0;
    if(args[1]==NULL){
        printf("Error:No File name\n");
        return 1;
    }
    if((fp=fopen(args[1],"r"))){
        fclose(fp);
        printf("File already exist please give another name\n");
        return 1;
    }else{ 
	    fp= fopen(args[1],"w"); 
        printf("File has been created\n");
        return 1;
    }
    
}