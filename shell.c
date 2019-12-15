#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "header.h"

/*
  Parse a string using the delimiter ch
  Returns an array of arguments
*/
char ** parse(char * line, char * ch) {
  char ** arr = malloc(100);
  int i;
  for (i = 0; line != NULL; i++) {
    arr[i] = strsep(&line, ch);
    // removes extraneous spaces
    if (strlen(arr[i]) == 0)
      i--;
  }
  arr[i] = NULL;
  return arr;
}

/*
  Execute the command
*/
void execute(char ** args) {
  // edge case: exit command
  if (strcmp(args[0], "exit") == 0){
    exit(0);
  }
  // edge case: cd command
  else if (strcmp(args[0], "cd") == 0){
    changeDirectory(args);
  }
  else forkExecute(args);
}

/*
  Changes the directory based on the given argument
  Returns 1 if no path is given, -1 if path does not exist,
          0 if path exists and chdir is successful
*/
int changeDirectory(char * args[]){
  char dir[100];
  if (args[1] == NULL) {
    chdir(getenv("HOME"));
    printf("%s\n", getcwd(dir, 100));
    return 1;
  }
  else {
    FILE *file = fopen(args[1], "r");
    if (file == NULL) {
      printf("%s: no such directory\n", args[1]);
      fclose(file);
      return -1;
    }
    else {
      chdir(args[1]);
      printf("%s\n", getcwd(dir, 100));
    }
  }
  return 0;
}

/*
  Forks and executes the command based on the given arguments
  Returns 0 if successful and -1 if there is an error
*/
int forkExecute(char ** args) {
  pid_t pid = fork();
  int status;
  // if (pid == 0){
  //   sleep(1);
  // }
  if (pid == -1) {
    char * error = strerror(errno);
    printf("error: %s\n", error);
    return -1;
  }
  if (pid > 0) {
    (waitpid(pid, &status, 0));
  } else {
    redirect(args);
    execvp(args[0], args);
    if (errno != 0){
      printf("command not found: %s \n", args[0]);
      kill(pid, SIGTERM);
      return -1;
    }
  }
  return 0;
}

/*
  Redirects based on the given arguments
  Returns 0 if successful and -1 if there is an error
*/
void redirect (char ** args) {
  int i;
  for (i = 0; args[i] != NULL; i++) {

    // redirect input
    if (strcmp(args[i], "<") == 0) {
      char * file = args[i+1];
      args[i] = NULL;
      int fd = open(file, O_RDONLY);
      dup2(fd, STDIN_FILENO);
      close(fd);
    }
    // redirect output, overwrite file
    else if (strcmp(args[i], ">") == 0) {
      char * file = args[i+1];
      args[i] = NULL;
      int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
      dup2(fd, STDOUT_FILENO);
      close(fd);
    }
    // redirect output, appends to file
    else if (strcmp(args[i], ">>") == 0) {
      char * file = args[i+1];
      args[i] = NULL;
      int fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
      dup2(fd, STDOUT_FILENO);
      close(fd);
    }
  }
}
