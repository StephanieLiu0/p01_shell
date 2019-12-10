#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#include "header.h"

int main() {
  printf("Enter commands to execute: ");
  char input[100];
  fgets(input, 100, stdin);

  char modInput[100];
  strncpy(modInput, input, strlen(input)-1);

  char ** cmds = parse(modInput, ";");
  for (int i = 0; cmds[i] != NULL; i++) {
    printf("\n");
    char ** args = parse(cmds[i], " ");
    execute(args);
  }
  printf("\n");

  return 0;
}
