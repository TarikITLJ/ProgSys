#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define prompt "fotune"
#define SIZE 128;


int main() {
    char buf[SIZE];
    //const char *message = "$ ./enseash \nBienvenue dans la shell ENSEA. \nPour quitter, tapez 'exit' \nenseash %\n";
    // write(STDOUT_FILENO, message, strlen(message));




    read(STDOUT_FILENO, buf, strlen(buf));
    write(STDOUT_FILENO,buf,strlen(buf));


    exit(EXIT_SUCCESS);
}
