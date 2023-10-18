#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

// gcc parte4.c -o parte4

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        printf("Meu pid: %d\n", getpid());
        while(1);
        exit(0);
    }
    
    sleep(5);
    int status;
    int wait_return = waitpid(filho, &status, WNOHANG);
    printf("wait_return: %d\n", wait_return);

    if(wait_return == 0){
        printf("Ainda não terminou, vou chamar kill!\n");
        kill(filho, SIGKILL);
    } else {
        printf("Filho já finalizou!\n");
    }

    printf("Exited: %d, Signaled: %d, TERMSIG: %d Error: %s\n", 
        WIFEXITED(status),
        WIFSIGNALED(status),
        WTERMSIG(status),
        strsignal(WTERMSIG(status))
    );
    return 0;
}