#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>


#define SIZE 4096

void printPrompt(int status,long duration) {
    char prompt[SIZE];

    if (WIFEXITED(status)) { 
        int exit_status = WEXITSTATUS(status);
        snprintf(prompt, SIZE, "enseash [exit:%d] %% ", exit_status,duration);
    } else if (WIFSIGNALED(status)){
        int signal = WTERMSIG(status);
        snprintf(prompt, SIZE, "enseash [sign:%d] %% ", signal,duration);
    } else { 
        snprintf(prompt, SIZE, "enseash %% ");
    }
    write(STDOUT_FILENO, prompt, strlen(prompt));
}

int main() {
    char buf[SIZE];
    ssize_t bytes_read;
    const char *prompt;
    int last_status = 0; // initialized for Q4

    const char *message = "$ ./enseash \nBienvenue dans la shell ENSEA. \nPour quitter, tapez 'exit'\n";
    write(STDOUT_FILENO, message, strlen(message));

    const char *message_exit = "Bye bye...\n";
    while(1){
        printPrompt(last_status);


        bytes_read = read(STDIN_FILENO, buf, SIZE-1);

        buf[bytes_read]='\0';
        buf[strcspn(buf,"\n")]='\0';
if (strcmp(buf,"exit")==0){
    write(STDOUT_FILENO,message_exit,strlen(message_exit));
    exit(EXIT_SUCCESS);
}

        int argc = 0;
            char *argv[SIZE] = {};
        char *token = strtok(buf, " ");

        // Configuration of argv
        while (token != NULL && argc < ((SIZE)-1))
        {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        if (argc == 0)
        { // Deals with the case when pressing "Enter"
            continue;
        }
        pid_t process = fork();

        if (process < 0)
        {
          perror("Fork failed");
           return -1;
        }

         if (process == 0) { // Child Process
            execvp(argv[0], argv);


            perror("Error: Command not found");
            exit(EXIT_FAILURE);
        } else { // Parent process
            
            waitpid(process, &last_status, 0);
        }
    
        

    }
    exit(EXIT_SUCCESS);
}
