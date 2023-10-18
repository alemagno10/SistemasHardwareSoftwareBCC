#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

// gcc parte3.c -o parte3

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        printf("Meu pid: %d\n", getpid());
        while(1);
        exit(0);
    }

    sleep(5);
    kill(filho, SIGKILL);

    int status;
    wait(&status);
    printf("Exited: %d, Signaled: %d, TERMSIG: %d Error: %s\n", 
        WIFEXITED(status),
        WIFSIGNALED(status),
        WTERMSIG(status),
        strsignal(WTERMSIG(status))
    );
    return 0;
}