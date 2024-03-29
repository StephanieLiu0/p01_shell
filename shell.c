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

/*======== char ** parse() ==========
Inputs: char * line
        char * ch
Returns: array of strings separated by the delimiter

Parses a line using the specified delimiter.
====================*/
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

/*======== void execute ==========
Inputs: (char ** args)
Returns:

Executes the command by calling different functions based on the arguments given.
If a pipe is present, myPipe(char ** args) is called.
If the command is exit, the program exits.
If the command is cd, changeDirectory(char * args[]) is called.
====================*/
void execute(char ** args) {
  // check for a pipe
  int pipe = 0;
  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], "|") == 0)
      pipe = 1;
  }
  if (pipe == 1){
    myPipe(args);
  }
  // edge case: exit command
  else if (strcmp(args[0], "exit") == 0){
    exit(0);
  }
  // edge case: cd command
  else if (strcmp(args[0], "cd") == 0){
    changeDirectory(args);
  }
  else forkExecute(args);
}

/*======== int changeDirectory() ==========
Inputs: char * args[]
Returns: 1 if the only arg is "cd" and no path is given
        -1 if the path does not exist
        0 if the path exists and chdir is successful

Changes the directory based on the argument (if any) given after "cd".
====================*/
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
      // printf("%s\n", getcwd(dir, 100));
    }
  }
  return 0;
}

/*======== int myPipe() ==========
Inputs: char ** args
Returns: -1 if one or both of the commands are invalid
        0 if successful

Pipes the commands based on the arguments.
====================*/

int myPipe(char ** args){
  FILE *inputCommand = popen(args[0], "r");
  FILE *outputCommand = popen(args[2], "w");
  if (!inputCommand || !outputCommand){
    printf("Error: %s\n", strerror(errno));
    return -1;
  }
  char cmds[100];
  while (fgets(cmds, 100, inputCommand)){
    fputs(cmds, outputCommand);
  }
  pclose(inputCommand);
  pclose(outputCommand);
  return 0;
}

/*======== int forkExecute() ==========
Inputs: char ** args
Returns: -1 if there is an error
        0 if successful

Forks and executes the command. If forking is unsuccessful, an errno is printed.
Otherwise, the parent process waits while the child process executes the command.
If the command is invalid, the process is terminated.
====================*/
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

/*======== void redirect () ==========
Inputs: char ** args
Returns: -1 if there is an error
        0 if successful

Redirects input if "<" present. If ">" present, output is redirected
into a file (by creating a new file or overwriting an existing file).
If ">>" present, output is redirected into a file (by creating a new file
or appending to an existing file).
====================*/
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
