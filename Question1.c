#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    const char *message = "$ ./enseash \nBienvenue dans la shell ENSEA. \nPour quitter, tapez 'exit' \nenseash %\n";
    write(STDOUT_FILENO, message, strlen(message));

    exit(EXIT_SUCCESS);

}

