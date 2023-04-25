/*
**********************************
*	Author : PAUL TOHMEH
*	Date : April 25 2023
**********************************
*/


#include "headers.h"


void execute_command(char **args){
    int pipes[2];
    pid_t pid;
    int status;
    int background = 0;
    pid_t prev_pid = 0;

    /* ----------------- PARTIE 7 -----------------
			        Implémentez le &
	   ----------------- PARTIE 7 -----------------
	*/  
    // Check if command should run in the background
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "&") == 0) {
            args[i] = NULL;
            background = 1;
            break;
        }
    }

    pid = fork();

    if (pid < 0){
        printf("Error: Fork failed.\n");
        exit(1);
    }
    else if(pid == 0){ // Child process
        int i, input_fd = 0, output_fd = 1, error_fd = 2, prev_i = -1;
        for (i = 0; args[i] != NULL; i++){

            /* ----------------- PARTIE 5 -----------------
			   > Implémentez la redirection d’entrées sorties standard
			   ----------------- PARTIE 5 -----------------
			*/  
         
            if (strcmp(args[i], ">") == 0) { // Output redirection
                output_fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
                args[i] = NULL;
                i++;
            }
            else if (strcmp(args[i], "<") == 0){ // Input redirection
                input_fd = open(args[i+1], O_RDONLY);
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
                args[i] = NULL;
                i++;
            }
            else if (strcmp(args[i], "2>") == 0){ // Error redirection
                error_fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(error_fd, STDERR_FILENO);
                close(error_fd);
                args[i] = NULL;
                i++;
            }
            /* ----------------- PARTIE 6 -----------------
			                 Implémentez les pipes
			   ----------------- PARTIE 6 -----------------
			*/  
            else if(strcmp(args[i], "|") == 0) {
                // Execute pipeline
                args[i] = NULL;
                int pipefd[2];
                pipe(pipefd);
                pid_t pid = fork();
                if(pid == 0) {
                    // Child process
                    close(pipefd[0]);
                    dup2(pipefd[1], STDOUT_FILENO);
                    execvp(args[0], args);
                } 
                else if(pid > 0) {
                    // Parent process
                    wait(NULL);
                    close(pipefd[1]);
                    dup2(pipefd[0], STDIN_FILENO);
                    execvp(args[i+1], args+i+1);
                } 
                else {
                    // Fork error
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
            }
        }
        execvp(args[0],args);
        exit(EXIT_FAILURE);
    }
    else{ // Parent process
        if (!background) {
            do{
                waitpid(pid, &status, WUNTRACED);
            }while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
}
