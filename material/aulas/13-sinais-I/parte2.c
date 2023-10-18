#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

// gcc parte2.c -o parte2

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        printf("Meu pid: %d\n", getpid());
        while(1);
    }

    int status;
    pid_t child = wait(&status);
    printf("Exited: %d, Signaled: %d, TERMSIG: %d Error: %s\n", 
        WIFEXITED(status),
        WIFSIGNALED(status),
        WTERMSIG(status),
        strsignal(WTERMSIG(status))
    );
    return 0;
}