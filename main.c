#include "sh_history.h"
#include "sh_exit.h"
#include "sh_cd.h"
#include "sh_ls.h"
#include "sh_play.h"
#include "sh_pwd.h"
#include "sh_remove.h"
#include "sh_date.h"
#include "sh_touch.h"
#include "sh_who.h"


#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LSH_RL_BUFSIZE 1024

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
int argc=0;

#define NUM 16

int sh_wc(char **args);
int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);
int sh_history(char **args);
int sh_ls(char **args);
int sh_play(char **args);
int sh_pwd(char **args);
int sh_remove(char **args);
int sh_date(char **args);
int sh_touch(char **args);
int sh_who(char **args);
int sh_echo(char **args);
int sh_append(char **args);
int sh_rename(char **args);
int sh_cp(char **args);

int (*builtin_func[]) (char **) = {
  &sh_append,
  &sh_cd,
  &sh_cp,
  &sh_date,
  &sh_echo,
  &sh_exit,
  &sh_help,
  &sh_history,
  &sh_ls,
  &sh_play,
  &sh_pwd,
  &sh_remove,
  &sh_rename,
  &sh_touch,
  &sh_wc,
  &sh_who,
  
};

char *builtin_str[] = {
  "append",
  "cd",
  "cp",
  "date",
  "echo",
  "exit",
  "help",
  "history",
  "ls",
  "play",
  "pwd",
  "remove",
  "rename",
  "touch",
  "wc",
  "who"
};

int sh_cp(char **argv)
{
    char buffer[1024];
    int files[2];
    ssize_t count;

    /* Check for insufficient parameters */
if(argc < 3) 
{
printf("Too few arguments to call copy");
return 1;
}
if(argc>3)
{
printf("The function needs exactly 2 command line parameters.");
return 1;
}
    files[0] = open(argv[1], O_RDONLY);
    
    if (files[0] == -1) /* Check if file opened */
        {
printf("Source file not opened");
exit(-1);
}
    files[1] = creat(argv[2],S_IRWXU|S_IWUSR|S_IRGRP|S_IROTH);
    if (files[1] == -1) /* Check if file opened (permissions problems ...) */
    {
        printf("Destination file not opened");
        close(files[0]);
        return 1;
    }

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
        write(files[1], buffer, count);

    close(files[0]);
    close(files[1]);
    return 1;
}

int sh_rename(char **args)
{
  if (argc < 3) {
      printf("Not enough command line parameters given!\n");
      return 1;
    } 
  int i,fd1,fd2;
  char *file1,*file2,buf[2];
  file1=args[1];
  file2=args[2];
 
  //fprintf(stderr,"Second argument %s\n",file2);
  //printf("file1=%s file2=%s",file1,file2);
  fd1=open(file1,O_RDONLY,0777);
  if (fd1 == -1) {
      fprintf(stderr,"File could not be opened, found or whatever, errno is %d\n",errno);
      return 1;
    }
  fd2=creat(file2,0777);
  while(i=read(fd1,buf,1)>0)
    write(fd2,buf,1);
  fprintf(stderr,"File is renamed successfully!\n");
  remove(file1);
  close(fd1);
  close(fd2);
  return 1;
}

int sh_append(char **argv)
{
    
  if(argc < 3) 
  {
  printf("Too few arguments to call copy\n");
  return 1;
  }
if(argc>3)
{
  printf("The function needs exactly 2 command line parameters.\n");
  return 1;
}
FILE *pFile;
FILE *pFile2;int n;
char buffer[256];

pFile=fopen(argv[1], "r");
pFile2=fopen(argv[2], "a");
if(pFile==NULL) {
    perror("Error opening file.");
}
else 
{
    while(!feof(pFile)) 
    {
        if((fgets(buffer, 100, pFile)) != NULL) 
        {
        buffer[256]='\0';
        //fseek(pFile2, -100, SEEK_END);
        fprintf(pFile2,"%s",buffer);
        }
    }
}
fclose(pFile);
fclose(pFile2);
return 1;
}

int sh_wc(char ** args){
  int bytes=0,words=0,lines=0;
  char buf;
  int space=1;
  if (argc < 2) {
      printf("Not enough command line parameters given!, Enter file name\n");
      return 1;
    }
    FILE *fd = fopen( args[1], "r");
    if (fd == 0) {
      fprintf(stderr,"File could not be opened, found or whatever, errno is %d\n",errno);
      return 1;
    }
    char *file=args[1];
    while(read(fileno(fd),&buf,1)==1){
      bytes++;
      if(buf==' ' || buf=='\t'){
        space=1;
      }
      else if(buf=='\n'){
        lines++;
        space=1;
      }
      else{
        if(space==1){
          words++;
        }
        space=0;
      }
    }
    printf("%d %d %d %s\n",lines,words,bytes,file);   
}

int sh_echo(char **args){
  int sz = argc,i;
  if (argc==1) {
    fprintf(stderr, "sh: expected argument to \"echo\"\n");
  } else{
    for(i=1;i<sz;i++){
      printf("%s ",args[i]);
    }
    printf("\n");
  }
}
int sh_help(char **args)
{
  int i;
  printf("Shell Help !\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < NUM; i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}
int sh_launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
   if (execvp(args[0], args) == -1) {
      perror("sh1");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
   
    perror("sh2");
  } else {
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int sh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    return 1;
  }

  for (i = 0; i < NUM; i++) 
  {
    //if(args[0][strlen(args[0])] == ' ')args[0][strlen(args[0])]='\0';
//    printf("%s",args[0]);
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return sh_launch(args);
}

char *sh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "sh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "sh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

char **sh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "sh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "sh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  argc=position;
  tokens[position] = NULL;
  return tokens;
}

void sh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = sh_read_line();
   // printf("1");
    insertToHistory(line);
   // printf("1");
    args = sh_split_line(line);
    //printf("1");
    status = sh_execute(args);
    //printf("1");
    free(line);
    free(args);
  } while (status);
}


int main()
{

  sh_loop();
  return EXIT_SUCCESS;
}
