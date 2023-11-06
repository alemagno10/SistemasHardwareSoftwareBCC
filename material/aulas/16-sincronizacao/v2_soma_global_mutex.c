#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// gcc soma_global_mutex.c -o soma_global_mutex

typedef struct {
    double *vetor;
    int start, end;
    pthread_mutex_t *mutex_soma;
} soma_parcial_args;

double soma = 0;
void *soma_parcial(void *_arg) {
    soma_parcial_args *spa = _arg;

    for (int i = spa->start; i < spa->end; i++) {
        pthread_mutex_lock(spa->mutex_soma);
        soma += spa->vetor[i];
        pthread_mutex_unlock(spa->mutex_soma);

    }

    return NULL;
}

int main(int argc, char *argv[]) {
    double *vetor = NULL;
    int n;
    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }

    int numThreads = 4;
    pthread_mutex_t mutex_soma = PTHREAD_MUTEX_INITIALIZER;


    /* TODO: criar thread_t e soma_parcial_args aqui */
    soma_parcial_args *args = malloc(sizeof(soma_parcial_args) * numThreads);
    pthread_t *threadsId = malloc(sizeof(pthread_t) * numThreads);
    int valuesPerThread = n/numThreads;
    
    for(int i = 0; i < numThreads; i++){
        /* TODO: preencher args e lançar thread */
        args[i].start = valuesPerThread * i;
        args[i].end = valuesPerThread * (i+1);
        args[i].vetor = vetor;
        args[i].mutex_soma = &mutex_soma;
        int status = pthread_create(&threadsId[i], NULL, soma_parcial, &args[i]);
    }

    /* TODO: esperar pela conclusão*/
    for(int i = 0; i < numThreads; i++){
        pthread_join(threadsId[i], NULL);
    }

    printf("Paralela: %lf\n", soma);

    soma = 0;
    soma_parcial_args *aa = malloc(sizeof(soma_parcial_args));
    aa->vetor = vetor;
    aa->start = 0;
    aa->end = n;
    aa->mutex_soma = &mutex_soma;
    soma_parcial(aa);
    printf("Sequencial: %lf\n", soma);

    return 0;
}
