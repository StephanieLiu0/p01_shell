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

int main() {
  char input[100];
  char ** args;

  while (1){
    printf("$ ");

    fgets(input, 100, stdin);
    input[strlen(input) - 1] = 0;

    char ** cmds = parse(input, ";");

    for (int i = 0; cmds[i] != NULL; i++) {
      args = parse(cmds[i], " ");
      //printf("%s\n", input);
      // if (strstr(input, "|") != NULL){
      // else if (strcmp(args[1], "|") == 0){
      //   printf("%s\n", input);
      //   myPipe(args);
      // }
      execute(args);
    }
    free(cmds);
  }
  return 0;
}
