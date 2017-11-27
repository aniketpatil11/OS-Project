#include <stdio.h>
#include <time.h>
#include "sh_date.h"

int sh_date(char **args){
    char temp[100];
    time_t current_time = time(NULL);
    struct tm *tm = localtime(&current_time);
    printf("Current Day, Date and Time: \n");
    printf("%s", asctime(tm));
    return 1;
}