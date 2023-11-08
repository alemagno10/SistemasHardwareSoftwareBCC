#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("WRONG USAGE!\n\nUSAGE:\n./q2_ref image price\n");
        return 0;
    }

    int attempts = 0;
    char strAttempts[20];
    int status;
    while(1){
        pid_t child = fork();

        if(child == 0){
            sprintf(strAttempts, "%d", attempts);
            char *ocrArgs[] = {"./ocr", argv[1], strAttempts, NULL};
            execvp(ocrArgs[0], ocrArgs);
            exit(EXIT_FAILURE);
        }

        wait(&status);
        if(WIFSIGNALED(status)){
            attempts++;
            printf("OCR TERMINOU COM SINAL %s\n", strsignal(WTERMSIG(status)));
        } else {
            printf("OCR TERMINOU NORMALMENTE!\n");
            printf("TIVEMOS UM GASTO TOTAL DE %.2f\n", (attempts+1) * (double)atoi(argv[2]));
            return 0;
        }
    }
}