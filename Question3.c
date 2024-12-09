#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define SIZE 1024


int main() {
    char buf[SIZE];
    ssize_t bytes_read;

    const char *message = "$ ./enseash \nBienvenue dans la shell ENSEA. \nPour quitter, tapez 'exit' \nenseash %\n";
    write(STDOUT_FILENO, message, strlen(message));


    const char *message_fortune = "Today is what happened yesterday\n";
    const char *bye_message = "Bye bye....";
    while(1){
        write(STDOUT_FILENO, "enseash % ", 10);
        bytes_read = read(STDOUT_FILENO, buf, SIZE-1);

        if (bytes_read<=0){
            break;
        }

        if(strcmp(buf, "fortune")==0){
            write(STDOUT_FILENO,message_fortune,strlen(message_fortune));
        }

        if (strcomp(buf, "exit")==0){
            write(STDOUT_FILENO,bye_message,strlen(bye_message));
        }
        
    }
    exit(EXIT_SUCCESS);
}
