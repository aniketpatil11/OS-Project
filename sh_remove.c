/*this code simulates REMOVE file command in ubuntu.Takes the file/folder name as input.

It does so by using remove(const char* filename)
		remove()  deletes  a  name from the filesystem.  

	   If the removed name was the last link to a file and no  processes  have
       the  file  open, the file is deleted and the space it was using is made
       available for reuse.

    If the name was the last link to a file, but any processes  still  have
    the  file  open,  the file will remain in existence until the last file
    descriptor referring to it is closed.

    Note:to delete a folder one must make sure that the following folder is empty
      */



#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include "sh_remove.h"
int sh_remove(char **args)
{
char fn[10];
printf("Enter source filename\n");
scanf("%s",fn);
if(remove(fn)==0)
printf("File removed\n");
else
printf("File cannot be removed\n");
return 1;
} 
