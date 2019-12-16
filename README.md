# p01_shell
*by Stephanie Liu and Christina Tan*

# Features
- Forks and executes commands
- Parses multiple commands on one line
- Redirects using <, >, >>
- Implements simple pipes

# Things to Know / Bugs
- Function can execute multiple commands in both of these formats: "cd;ls" or "cd ; ls"
- Program cannot detect pipes like the spacing above; the function terminates if there is no spaces between the pipe symbol and the commands
- Program terminates entirely if given a nonexistent command
- Command line input limited to 100 characters
- Expects the last character in the command line input to be a new line, so the last character is always removed

# Files and function headers
shell.c
*handles all functions necessary for parsing and executing:

      /*======== char ** parse() ==========
      Inputs: char * line
              char * ch
      Returns: array of strings separated by the delimiter

      Parses a line using the specified delimiter.
      ====================*/


      /*======== void execute ==========
      Inputs: (char ** args)
      Returns:

      Executes the command by calling different functions based on the arguments given.
      If a pipe is present, myPipe(char ** args) is called.
      If the command is exit, the program exits.
      If the command is cd, changeDirectory(char * args[]) is called.
      ====================*/


      /*======== int changeDirectory() ==========
      Inputs: char * args[]
      Returns: 1 if the only arg is "cd" and no path is given
              -1 if the path does not exist
              0 if the path exists and chdir is successful

      Changes the directory based on the argument (if any) given after "cd".
      ====================*/


      /*======== int myPipe() ==========
      Inputs: char ** args
      Returns: -1 if one or both of the commands are invalid
              0 if successful

      Pipes the commands based on the arguments.
      ====================*/


      /*======== int forkExecute() ==========
      Inputs: char ** args
      Returns: -1 if there is an error
              0 if successful

      Forks and executes the command. If forking is unsuccessful, an errno is printed.
      Otherwise, the parent process waits while the child process executes the command.
      If the command is invalid, the process is terminated.
      ====================*/


      /*======== void redirect () ==========
      Inputs: char ** args
      Returns: -1 if there is an error
              0 if successful

      Redirects input if "<" present. If ">" present, output is redirected
      into a file (by creating a new file or overwriting an existing file).
      If ">>" present, output is redirected into a file (by creating a new file
      or appending to an existing file).
      ====================*/


main.c

*reads input from the command line and displays prompt

      /*======== int main () ==========
      Inputs:
      Returns: 0 when exiting shell

      While loop keeps user in shell until the exit command is called or
      an invalid command is called.
      ====================*/
