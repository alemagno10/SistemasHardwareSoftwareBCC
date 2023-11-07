#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

typedef struct{
    char *palavra; // palavra a ser classificada
    int res;       // retorno da thread virá aqui!
} t_arg;

#define MAX_LINE_LENGTH 256

/*
 * Função que simula a classificação de uma palavra
 */
int classifier(char *palavra){
    int sleep_time = rand() % 1 + 4;

    sleep(sleep_time);
    int soma = 157;
    for (int i = 0; palavra[i] != '\0'; i++){
        soma += palavra[i];
    }

    int res = (soma % 3);
    return res;
}

/*
 * Classificação em Threads!
 */
void *classifier_thread(void *_arg){
    t_arg *arg = _arg;
    arg->res = classifier(arg->palavra);
}

/* Função que lê uma palavra de um arquivo.
 * Considere que cada linha do arquivo contem apenas uma palavra.
 *
 * Entradas:
 *   int fd: descritor do arquivo
 *
 * Saída:
 *   Ponteiro (char *) para uma string com a palavra lida (sem \n). Caso o arquivo termine, retorne NULL.
 */
char *read_line(int fd, int *len){
    char buffer[1];
    int response ;
    char *word = malloc(sizeof(char) * 100);
    int idx = 0;

    while(1){
        response = read(fd, buffer, sizeof(buffer));
        if(response == 0){
            return NULL;
        } else if(buffer[0] != '\n'){
            word[idx++] = buffer[0];
        } else {
            break;
        }
    }

    if(idx==0) return NULL;
    word[idx] = '\0';
    (*len)++;
    return word;
}

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("USAGE:\n./q4 <n_threads> <file_name>\n");
        return 0;
    }

    int n_threads = atoi(argv[1]); // Info da linha de comando
    char *file_name = argv[2];     // Info da linha de comando

    int fd1 = open(file_name, O_RDONLY);

    if (fd1 == -1){
        fprintf(stderr, "Falha ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    int threads_limit = n_threads;
    pthread_t *tids = malloc(sizeof(pthread_t) * threads_limit);
    t_arg **args = malloc(sizeof(t_arg *) * threads_limit);
    char **words = malloc(sizeof(char*) * 100);
    int len = 0, i = 0;

    while(1){
        char *palavra = read_line(fd1, &len);
        if (palavra == NULL){
            break;
        }
        words[i++] = palavra;
    }

    int threads_created = 0; // Quantas threads criei de fato
    int result[] = {0,0,0};
    int running = n_threads;
    int len2 = len;

    for(int k=0; k<ceil((double)len2/n_threads); k++){
        for(int i = 0; i<running; i++){
            if(len < n_threads) running = len;
            int idx = (k*n_threads)+i;

            t_arg *arg = malloc(sizeof(t_arg));
            arg->palavra = words[idx];
            
            if (threads_limit == threads_created){
                threads_limit *= 2;
                tids = realloc(tids, sizeof(pthread_t) * threads_limit);
                args = realloc(args, sizeof(t_arg *) * threads_limit);
            }

            args[idx] = arg;

            pthread_create(&tids[idx], NULL, classifier_thread, arg);
            printf("CRIOU THREAD %02d PARA PROCESSAR A PALAVRA %s\n", idx, arg->palavra);

            threads_created++;
        }
        len -= n_threads;
    }

    for(int i = 0; i<len2; i++){
        pthread_join(tids[i], NULL);
        printf("THREAD %02d TERMINOU COM O RESULTADO %d\n", i, args[i]->res);
        result[args[i]->res]++;
    }

    printf("RESULTADO:\n");
    for(int i = 0; i<3; i++){
        printf("TOTAL CLASSE %d, %d\n", i, result[i]);
    }

    return 0;
}
