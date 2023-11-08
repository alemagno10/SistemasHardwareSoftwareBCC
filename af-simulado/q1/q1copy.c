// Leia o README antes de iniciar este exercício!

// inclua as bibliotecas necessárias
// #include ...
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct {
    pthread_mutex_t *mutex;
} args;

sem_t barrier;
sem_t barrier2;

int waiting;
int waiting2;

void runBarrier(sem_t *barrier, pthread_mutex_t *mutex, int *wait);

void *thread1(void *args_){
    args *threadArg = args_;

    printf("A\n");
    runBarrier(&barrier, threadArg->mutex, &waiting);
    runBarrier(&barrier2, threadArg->mutex, &waiting2);

    return NULL;
}

void *thread2(void *args_){
    args *threadArg = args_;

    runBarrier(&barrier, threadArg->mutex, &waiting);
    printf("B\n");
    runBarrier(&barrier2, threadArg->mutex, &waiting2);
    printf("C\n");

    return NULL;
}

void *thread3(void *args_){
    args *threadArg = args_;

    runBarrier(&barrier, threadArg->mutex, &waiting);
    printf("D\n");
    runBarrier(&barrier2, threadArg->mutex, &waiting2);
    printf("E\n");

    return NULL;
}

void *thread4(void *args_){
    args *threadArg = args_;

    printf("F\n");
    runBarrier(&barrier, threadArg->mutex, &waiting);
    printf("G\n");
    runBarrier(&barrier2, threadArg->mutex, &waiting2);

    return NULL;
}

void runBarrier(sem_t *barrier, pthread_mutex_t *mutex, int *wait){
    pthread_mutex_lock(mutex);
    (*wait)++;
    pthread_mutex_unlock(mutex);

    if(*wait < 4){
        sem_wait(barrier);
    } else {
        for(int i = 0; i<3; i++){
            sem_post(barrier);
        }
    }
}

int main(int argc, char *argv[]){
    args *threadArgs = malloc(sizeof(args) * 4);
    pthread_t *threadIds = malloc(sizeof(pthread_t) * 4);

    sem_init(&barrier,0,0);
    sem_init(&barrier2,0,0);

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    void* (*functions[])(void*) = {thread1, thread2, thread3, thread4};

    for(int i = 0; i<4; i++){
        threadArgs[i].mutex = &mutex;
        int status = pthread_create(&threadIds[i], NULL, functions[i], &threadArgs[i]);
    }

    for(int i = 0; i<4; i++){
        pthread_join(threadIds[i], NULL);
    }

    sem_destroy(&barrier);
    sem_destroy(&barrier2);
    return 0;
}