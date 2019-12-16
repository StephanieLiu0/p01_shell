char ** parse(char * line, char * ch);

void execute(char ** args);

int changeDirectory(char * args[]);

int myPipe(char ** args);

int forkExecute(char ** args);

void redirect (char ** args);
