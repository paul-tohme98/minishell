#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LENGTH 256 // Maximum length of the command
#define MAX_ARGS 10 // Maximum number of arguments per command
#define MAX_CMD_LEN 100

void execute_command(char** );
void execute_pipe_command(char** , int );
