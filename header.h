#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

char ** parse(char * line, char * ch);
char ** parse_multi_lines(char * line);
int execute(char ** args);
int changeDirectory(char * args[]);
