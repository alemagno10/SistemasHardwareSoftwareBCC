// Leia o PDF ou MD antes de iniciar este exercício!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>

// gcc q3.c -o q3

// Variável GLOBAL para armazenar o valor de PI aproximado
double pi = 0.0;

// Função que gera um numero aleatorio uniformemente entre 0.0 e 1.0
// Você não deve alterar esta função
double random_zero_one() {
    return (double)random()/(double)RAND_MAX;
}

// Função que calcula o valor de pi por simulação (Monte Carlo)
// Você não deve alterar esta função
double aproxima_pi() {
    long dentro = 0;
    long total_pontos = 0;

    double x,y,d;
    while (1) {
        x = random_zero_one();
        y = random_zero_one();
        d = x*x + y*y;
        if (d<=1) {
            dentro++;
        }
        total_pontos++;
        pi = 4.0 * ((double)dentro/(double)total_pontos);
        if (random_zero_one() < 0.008) {
            sleep(1);
        }
    }
}

// Crie AQUI a função que exporta o valor de pi para um arquivo chamado pi.txt
// Esta função deve ser chamada pelo handler quando este for acionado
void toTXT(){
    int fd = open("pi.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    char number[50];
    sprintf(number, "%f", pi);
    write(fd, &number, sizeof(double));
    close(fd);
}

// Crie AQUI a função que será o handler do sinal
void sig_handler(int num){
    toTXT();

    struct sigaction handler;
    handler.sa_handler = SIG_DFL;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGINT, &handler, NULL);
    kill(getpid(), SIGINT);
}

int main(){

    // Exiba o PID deste processo
    printf("pid: %d\n", getpid());

    // Registre AQUI seu handler para o sinal SIGINT!
    struct sigaction handler;

    handler.sa_handler = sig_handler;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGINT, &handler, NULL);

    srand(time(NULL));
    aproxima_pi();

    return 0;
}