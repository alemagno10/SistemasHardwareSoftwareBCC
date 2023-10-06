#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t filho;

    filho = fork();

    if (filho == 0) {
        printf("Acabei filho\n");
        exit(0);
    }

    wait(NULL);
    printf("Acabou!\n");

    return 0;
}
