#include "sh_history.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HISTORY_SZ 20
#define WORD_SZ 128
char history[HISTORY_SZ][WORD_SZ];
int head = HISTORY_SZ;
int tail = HISTORY_SZ-1;
void insertToHistory(char *cmd){
	if(head>0){
		head=head-1;
		strcpy(history[head],cmd);
	}
	else if(head==0){
		head = HISTORY_SZ-1;
		strcpy(history[head],cmd);
	}

	if(tail==head){
		tail--;
	}

}
int sh_history(char **args){
	int i;
	if(head<=tail){
		for(i=head;i<=tail;i++){
			printf("%s\n",history[i]);
		}
	}
	else if(head>tail){
		for(i=head;i<=HISTORY_SZ;i++){
			printf("%s\n",history[i]);
		}
		for(i=0;i<=tail;i++){
			printf("%s\n",history[i]);
		}

	}
	return 1;
}

