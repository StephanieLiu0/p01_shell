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

int execute(char ** args) {
  pid_t pid = fork();
  int status;
  if (pid > 0)
    (waitpid(pid, &status, 0));
  else
    execvp(args[0], args);
  if (WIFEXITED(status))
    return WEXITSTATUS(status);
  return -1;
}
