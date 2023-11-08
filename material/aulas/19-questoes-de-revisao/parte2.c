#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

// linha de compilação: 

/* declarar tarefas aqui e lançar no main */
/* cada bloco na figura deverá ser representado por um print com sua letra */

typedef struct {
    pthread_mutex_t *mutex;
} args;

sem_t sem_barrier1;
sem_t sem_barrier2;
int bar1 = 0;
int bar2 = 0;

void barrier(sem_t *sem_bar, pthread_mutex_t *mutex, int *waiting, int numOfThreads);

void *thread1(void *arg_){
    args *threadArg = arg_; 

    printf("A\n");
    barrier(&sem_barrier1, threadArg->mutex, &bar1, 2);
    printf("C\n");

    return NULL;
}

void *thread2(void *arg_){
    args *threadArg = arg_; 

    printf("B\n");
    barrier(&sem_barrier1, threadArg->mutex, &bar1, 2);
    barrier(&sem_barrier2, threadArg->mutex, &bar2, 3);
    printf("D\n");

    return NULL;
}

void *thread3(void *arg_){
    args *threadArg = arg_; 

    printf("E\n");
    barrier(&sem_barrier2, threadArg->mutex, &bar2, 3);
    printf("F\n");

    return NULL;
}

void *thread4(void *arg_){
    args *threadArg = arg_;

    printf("G\n");
    barrier(&sem_barrier2, threadArg->mutex, &bar2, 3);
    printf("H\n"); 

    return NULL;
}

void barrier(sem_t *sem_bar, pthread_mutex_t *mutex, int *waiting, int numOfThreads){
    pthread_mutex_lock(mutex);
    (*waiting)++;
    pthread_mutex_unlock(mutex);

    if(*waiting < numOfThreads){
        sem_wait(sem_bar);
    } else {
        for(int i = 0; i<numOfThreads-1; i++){
            sem_post(sem_bar);
        }
    }
}


int main() {
    int N = 4;
    pthread_t *threadIds = malloc(sizeof(pthread_t) * N);
    args *threadArgs = malloc(sizeof(args) * N);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    void* (*functions[])(void*) = {thread1, thread2, thread3, thread4};

    for (int i = 0; i < N; i++) {
        threadArgs[i].mutex = &mutex;
        int status = pthread_create(&threadIds[i], NULL, functions[i], &threadArgs[i]);
    }

    for(int i = 0; i<N; i++){
        pthread_join(threadIds[i], NULL);
    }

    // Destroi os recursos
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem_barrier1);
    sem_destroy(&sem_barrier2);

    return 0;
}
