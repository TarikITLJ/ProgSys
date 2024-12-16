#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

#define SIZE 4096

void printPrompt(int status,long duration) {
    char prompt[SIZE];

    if (WIFEXITED(status)) {  // If the command returns an exit
        int exit_status = WEXITSTATUS(status);
        snprintf(prompt, SIZE, "enseash [exit:%d|%ldms] %% ", exit_status, duration);
    } else if (WIFSIGNALED(status)){ // If it is a signal
        int signal = WTERMSIG(status);
        snprintf(prompt, SIZE, "enseash [sign:%d|%ldms] %% ", signal, duration);
    } else { // If neither, print the prompt only
        snprintf(prompt, SIZE, "enseash %% ");
    }
    write(STDOUT_FILENO, prompt, strlen(prompt));
}


long Duration(struct timespec start, struct timespec end) {   // Convert Nanoseconds (and seconds) in Milliseconds
    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    return seconds * 1000 + nanoseconds / 1000000;
}

int main() {
    // Variables
    char buf[SIZE];
    ssize_t bytes_read;
    const char *prompt;
    int last_status = 0; // Initialized for Q4
    long duration = 0; // Initialized for Q5
    const char *message = "$ ./enseash \nBienvenue dans la shell ENSEA. \nPour quitter, tapez 'exit'\n";
    const char *message_exit = "Bye bye...\n";


    write(STDOUT_FILENO, message, strlen(message));     // Write the introduction to the shell

    while(1){
        printPrompt(last_status,duration); // prints the return of the previous command in the prompt and the duration

        bytes_read = read(STDIN_FILENO, buf, SIZE-1); // Reads the input command of the user
        buf[bytes_read]='\0';
        buf[strcspn(buf,"\n")]='\0';

        if (strcmp(buf,"exit")==0){  // If the written command corresponds to "exit", writes the exit message
            write(STDOUT_FILENO,message_exit,strlen(message_exit)); 
            exit(EXIT_SUCCESS);
        }

        int argc = 0;
        char *argv[SIZE] = {};
        char *token = strtok(buf, " ");

        // Configuration of argv and splitting it in two parts (command and arguments)
        while (token != NULL && argc < ((SIZE)-1))
        {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        if (argc == 0){ // Deals with the case when pressing "Enter"
            continue;
        }



        struct timespec start_time, end_time;
        clock_gettime(CLOCK_MONOTONIC, &start_time); // Initialize the value of start_time

        pid_t process = fork();

        if (process < 0)
        { // Handles possible errors when calling the fork
            perror("Fork failed");
            return -1;
        }

            if (process == 0) { // Child Process
            execvp(argv[0], argv);


            perror("Error: Command not found");
            exit(EXIT_FAILURE);
        } else { // Parent process
            
            waitpid(process, &last_status, 0);
            clock_gettime(CLOCK_MONOTONIC, &end_time); // Initialize the value of end_time
            duration = Duration(start_time, end_time); // CCalculate the duration of the execution
        }
    
        

    }
    exit(EXIT_SUCCESS);
}
