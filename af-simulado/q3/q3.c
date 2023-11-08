// Leia o PDF ou MD antes de iniciar este exercício!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

// Variável Global para o handler saber até qual linha processou
int linha_proc = 0;

// Função que gera um numero aleatorio uniformemente entre 0.0 e 1.0
// Você não deve alterar esta função
double random_zero_one(){
    return (double)random() / (double)RAND_MAX;
}

void brilha_brilha_estrelinha(){
    if (random_zero_one() < 0.5){
        sleep(1);
    }
}

int processa_linhas(int qt_linhas)
{
    for (linha_proc = 0; linha_proc < qt_linhas; linha_proc++)
    {
        brilha_brilha_estrelinha();
        printf("PROCESSOU A LINHA %d\n", linha_proc);
        fflush(stdout);
    }
}

// Crie AQUI a função que exporta o valor de `linha_proc` para um arquivo chamado q3_status.txt
// O arquivo deve ter apenas uma linha contendo, LINHA_PROC seguido de um sinal de igual e
// seguido da última linha processada, seguido de \n:
// LINHA_PROC=15
// Esta função deve ser chamada pelo handler quando este for acionado

void toTXT(){
    char str[100];
    sprintf(str,"LINHA_PROC=%d",linha_proc);
    int fd = open("q3_status.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    write(fd, str, strlen(str));
    close(fd);
}

// Crie AQUI a função que será o handler do sinal
void sigint_handler(int num){
    struct sigaction handler;
    handler.sa_handler = SIG_DFL;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGINT, &handler, NULL);
    toTXT();
    kill(getpid(), SIGINT);  
}

void sigterm_handler(int num){
    struct sigaction handler;
    handler.sa_handler = SIG_DFL;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGTERM, &handler, NULL);
    toTXT();
    kill(getpid(), SIGINT);  
}


int main(int argc, char *argv[]){

    if (argc < 2){
        printf("USAGE:\n./q4 n_lines\n");
        return EXIT_FAILURE;
    }

    printf("Meu pid: %d\n", getpid());

    // Registre AQUI seu handler para os sinais SIGINT e SIGTERM!
    struct sigaction handler;

    handler.sa_handler = sigint_handler;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGINT, &handler, NULL);

    handler.sa_handler = sigterm_handler;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGTERM, &handler, NULL);

    processa_linhas(atol(argv[1]));

    return 0;
}