#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int i;
    for(i = 0; i<8; i++){
        pid_t pid = fork();

        if(pid == 0){
            printf("Eu sou um processo filho, pid=%d, ppid=%d, meu id do programa é %d\n", getpid(), getppid(), i+1);
            exit(0);
        }
    }

    
    for (i = 0; i < 8; i++) {
        wait(NULL); // Espera pelos processos filhos terminarem
    }
    printf("Eu sou o processo pai, pid=%d, meu id do programa é 0\n", (int)getpid());
    
    return 0;
}