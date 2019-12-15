#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#include "header.h"

char ** parse(char * line, char * ch) {
  char ** arr = malloc(100);
  int i;
  for (i = 0; line != NULL; i++) {
    arr[i] = strsep(&line, ch);
  }
  arr[i] = NULL;
  return arr;
}

char ** parse_multi_lines(char * line){
  return parse(line, ";");
}

void execute(char ** args) {
  if (strcmp(args[0], "exit") == 0){
    exit(0);
  } else if (strcmp(args[0], "cd") == 0){
    changeDirectory(args);
  } else forkExecute(args);
}

int forkExecute(char ** args) {
  pid_t pid = fork();
  int status;
  // if (pid == 0){
  //   sleep(1);
  // }
  if (pid == -1){
    char * error = strerror(errno);
    printf("error: %s\n", error);
    return 1;
  }
  if (pid > 0){
    (waitpid(pid, &status, 0));
  } else
    execvp(args[0], args);
  if (WIFEXITED(status)){
    //printf("%d\n", WEXITSTATUS(status));
    // printf("%d\n", WTERMSIG(status));
  }
  return -1;
}

int changeDirectory(char * args[]){
  char dir[100];
  if (args[1] == NULL){
    chdir(getenv("HOME"));
    printf("%s\n", getcwd(dir, 100));
    return 1;
  } else {
    FILE *fptr = fopen(args[1], "r");
    if (fptr == NULL) {
      printf("%s: no such directory\n", args[1]);
      fclose(fptr);
      return -1;
    } else {
      chdir(args[1]);
      printf("%s\n", getcwd(dir, 100));
    }
  }
  return 0;
}
