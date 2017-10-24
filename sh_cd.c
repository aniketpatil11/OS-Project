#include "sh_cd.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int sh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "sh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("sh");
    }
  }
  return 1;
}