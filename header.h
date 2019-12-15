char ** parse(char * line, char * ch);

char ** parse_multi_lines(char * line);

void execute(char ** args);

int forkExecute(char ** args);

int changeDirectory(char * args[]);
