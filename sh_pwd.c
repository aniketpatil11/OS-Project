/*this code simulates working of pwd
i.e it print's name of current/working directory

it uses FILE management libraries present in c.
it contains call's to functions ->> 
1)popen(const char *command, const char *type)
    opens a process by creating a pipe,  forking,  and invoking  the shell. 
2)char *strtok(char *str, const char *delim)
    char *strtok(char *str, const char *delim);
    . 

*/



#ifdef __unix__
    #define IS_POSIX 1
    #define _BSD_SOURCE
#else
    #define IS_POSIX 0
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sh_pwd.h"

int sh_pwd(char **args)
{
    if (IS_POSIX == 1) {
        char buffer[500];
        FILE *output;

        // read output of a command
        output = popen("/bin/pwd", "r");
        char *pwd = fgets(buffer, sizeof(buffer), output);

        // strip '\n' on ending of a line
        pwd = strtok(pwd, "\n");

        puts("Path info by execute shell command 'pwd':");
        printf("\tWorkdir: %s\n", pwd);
        printf("\tFilepath: %s/%s\n", pwd, __FILE__);
    }
    return 1;
}