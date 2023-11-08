// Leia o PDF ou MD antes de iniciar este exercício!

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int ret;
    int wst;

    char *siscoinArgs[] = {"./siscoin", argv[1], argv[2], argv[3], NULL};

    if(argc < 4){
        if(getpid() == getpgrp()){
            printf("Argumentos faltando!\n");
        }
        return 0;
    }

    do {
        pid_t child = fork();

        if(child == 0){
            int response = execvp(siscoinArgs[0], siscoinArgs);
            printf("%d\n", response);
            if(response == -1){
                printf("erro ao executar siscoin\n");
                perror("execvp");
                exit(5);
            } else {
                exit(response);
            }
        }

        int status;
        wait(&status);

        ret = WEXITSTATUS(status);
        // Construa a chamada do executavel siscoin. Veja enunciado.
        // No pai, espere e trate o resultado
        // DICA: ao atribuir o return do siscoin, faça casting para (char)


    } while (ret > 0 && ret != 5); 
    // Repita enquanto houver falha. 
    // Para se tem problema com o valor ou a qtde de parâmetros
    // Esta validação está sendo feita em siscoin
    printf("Transferencia realizada!\n");
    return 0;
}