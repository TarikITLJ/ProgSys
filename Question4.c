#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define SIZE 4096


int main() {
    char buf[SIZE];
    ssize_t bytes_read;
    const char *prompt;

    const char *message = "$ ./enseash \nBienvenue dans la shell ENSEA. \nPour quitter, tapez 'exit'\n";
    write(STDOUT_FILENO, message, strlen(message));

    const char *message_exit = "Bye bye...\n";
    while(1){
        write(STDOUT_FILENO, "enseash % ", 10);

        bytes_read = read(STDIN_FILENO, buf, SIZE-1);

        buf[bytes_read]='\0';
        buf[strcspn(buf,"\n")]='\0';


        if(strcmp(buf, "fortune")==0){
            if (0==fork()){
                prompt = "fortune";
                execlp("/usr/games/fortune","fortune",NULL);
            }
            else{
                int status;
                wait(&status);
            }
        }
        else if (strcmp(buf,"exit")==0){
            prompt = "exit";
            write(STDOUT_FILENO,message_exit,strlen(message_exit));
            exit(EXIT_SUCCESS);
        }
        else{
            write(STDOUT_FILENO,"Commande non reconnue\n",22);
        }
        



    }
    exit(EXIT_SUCCESS);
}
