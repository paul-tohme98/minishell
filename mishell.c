/*
**********************************
*	Author : PAUL TOHMEH
*	Date : April 25 2023
**********************************
*/


#include "functions.c"

int main(){
    char *args[MAX_ARGS];
	char cwd[1024];
	int shell_open = 1;
	int i = 0;

	while(shell_open){
		fflush(stdout); // clear the output buffer

		char* str;
		str = (char*)malloc(MAX_LENGTH * sizeof(char));

		char* token;
		token = (char*)malloc(MAX_LENGTH * sizeof(char));

		char* line;
		line = (char*)malloc(MAX_LENGTH * sizeof(char));
		
		/* ----------------- PARTIE 3 -----------------
			> Modifiez également le shell pour qu’il 
			  affiche le répertoire courant avant
			  l’invite
		   ----------------- PARTIE 3 -----------------
		*/
		if(getcwd(cwd, sizeof(cwd)) != NULL){
        printf("%s %s ", cwd, "%");
		} 
		else{
			perror("getcwd() error");
			exit(EXIT_FAILURE);
		}

		fgets(str, MAX_LENGTH, stdin); // get the entered command from the user input
		for(int c = 0; c < MAX_LENGTH; c++){
			line[c] = str[c];
		}
		str[strcspn(str, "\n")] = 0; // remove trailing newline
		
		/* ----------------- PARTIE 4 -----------------
		   > Implémentez l’exécution de commandes simples
		   ----------------- PARTIE 4 -----------------
		*/
		args[0] = strtok(line, " \n"); // Split command string into arguments
		for (i = 1; i < MAX_ARGS; i++){
			args[i] = strtok(NULL, " \n");
			if (args[i] == NULL) {
				break;
			}
		}
		/*  ----------------- PARTIE 1 & 2 -----------------
			> Read the command passed by the user
		    > Parse the command into tokens and print 
			each one on a new line
			----------------- PARTIE 1 & 2 -----------------
		*/
		while ((token = strsep(&str, " ")) != NULL){ 
			if(strcmp(token, "exit") == 0){ // manage "exit"
				printf("Exiting...\n");
				exit(0);
			}
			// printf("%s\n", token); // Print each command on a new line
			/* ----------------- PARTIE 3 -----------------
			   > Exit the shell if the user enters : "exit"
			   > Change directory to the one passed in
			     argument by the user in the cmd : cd <dir>
			   ----------------- PARTIE 3 -----------------
			*/
			
			if(strcmp(token, "cd") == 0){ // manage "cd"
                char* dir = strsep(&str, " "); // get the argument to cd
                if (dir == NULL) {
                    printf("cd: missing argument\n");
                } else {
                    int ret = chdir(dir);
                    if (ret != 0) {
                        printf("cd: %s No such file or directory\n", dir);
                    }
                }
			}
		}

		/* ----------------- PARTIE 4 -------------------
		    Implémentez l’exécution de commandes simples
		   ----------------- PARTIE 4 -------------------
		*/
		if (feof(stdin)){ // Handle built-in commands 
            exit(0); 
			shell_open = 0;
		}
		// execute a command that is not exit, cd or ls
		else{
			execute_command(args);
		}
		free(str);
		free(token);
	}
	printf("\n");

	return 0;
}
