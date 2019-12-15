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
  char input[100];
  int x;
  char ** args;
  while (1){
    printf("$ ");

    fgets(input, 100, stdin);
    input[strlen(input) - 1] = 0;

    char ** cmds = parse_multi_lines(input);
    for (int i = 0; cmds[i] != NULL; i++) {
      args = parse(cmds[i], " ");
      execute(args);
    }
    free(cmds);
  }
  return 0;
}
