#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc -o exec exec.c

int main(){
    char *args[] = {"./ex1", "10", "20", "100", "abc", NULL};
    if(execvp(args[0], args) == -1){
        perror("execvp failed!");
        exit(EXIT_FAILURE);
    }
    return 0;
}
