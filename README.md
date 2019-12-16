# p01_shell
*by Stephanie Liu and Christina Tan*

# Features
- Forks and executes commands
- Parses multiple commands on one line
- Redirects using >, <
- 

# Bugs:
- Function can execute multiple commands in both of these formats: "cd;ls" or "cd ; ls"
- Program cannot detect pipes like the spacing above; the function terminates if there is no spaces between the pipe symbol and the commands
-

# Files and function headers
shell.c 

*handles all of the main commands: parsing, executing, cd, piping, and redirection*

    - char ** parse(char * line, char * ch);
      Parse a string using the delimiter ch
      Returns an array of arguments

    - void execute(char ** args);
      Executes the command based on the arguments given

    - int changeDirectory(char * args[]);
      Changes the directory based on the given argument
      Returns 1 if no path is given, -1 if path does not exist, 0 if path exists and chdir is successful

    - int myPipe(char ** args);
      Pipes the commands based on the given arguments
      Returns -1 if one or both of the commands are invalid, 0 if sucessful

    - int forkExecute(char ** args);
      Forks and executes the command based on the given arguments
      Returns 0 if successful and -1 if there is an error

    - void redirect (char ** args);
      Redirects based on the given arguments
      Returns 0 if successful and -1 if there is an error

main.c

*reads input from the command line and displays prompt*
