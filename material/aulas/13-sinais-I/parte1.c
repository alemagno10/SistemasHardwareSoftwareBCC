#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

// gcc parte1.c -o parte1

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        int i = 1/0;
        printf("Divisão por zero!\n");
        exit(0);
    }

    int status;
    pid_t child = wait(&status);
    printf("Meu pid: %d\n", child);
    printf("Exited: %d, Signaled: %d, TERMSIG: %d Error: %s\n", 
        WIFEXITED(status),
        WIFSIGNALED(status),
        WTERMSIG(status),
        strsignal(WTERMSIG(status))
    );
    return 0;
}