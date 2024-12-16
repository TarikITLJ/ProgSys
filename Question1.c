#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define prompt "enseash % "
#define SIZE 4096

int main() {
    const char *message = "$ ./enseash \nBienvenue dans la shell ENSEA. \nPour quitter, tapez 'exit'\n";
    char buf[SIZE];
    write(STDOUT_FILENO, message, strlen(message));
    while(1){
        write(STDOUT_FILENO,prompt, strlen(prompt));
        read(STDIN_FILENO,buf,4097);
    }
    exit(EXIT_SUCCESS);

}


