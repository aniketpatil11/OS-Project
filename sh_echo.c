#include "sh_echo.h"
#include <stdio.h>
#include <stdlib.h>
int sh_echo(char **args){
	int sz = argc;
	if (argc==1) {
    fprintf(stderr, "sh: expected argument to \"echo\"\n");
  } else{
  	printf("\n");
  	for(i=0;i<sz;i++){
  		printf("%s",args[i]);
  	}
  	printf("\n");
  }
}