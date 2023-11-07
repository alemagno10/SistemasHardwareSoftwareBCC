// Leia o PDF ou MD antes de iniciar este exercício!


// Faça os includes necessários aqui
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t barrier;
sem_t barrier2;

int waiting;
int waiting2;

typedef struct {
    pthread_mutex_t *mutex;
} args;

void *thread1(void *_arg) {
    args *threadArgs = _arg;

    printf("A\n");

    pthread_mutex_lock(threadArgs->mutex);
    waiting++;
    pthread_mutex_unlock(threadArgs->mutex);

    if(waiting < 4){
        sem_wait(&barrier);
    } else {
        for(int i = 0; i<3; i++){
            sem_post(&barrier);
        }
    }

    pthread_mutex_lock(threadArgs->mutex);
    waiting2++;
    pthread_mutex_unlock(threadArgs->mutex);

    if(waiting2 < 4){
        sem_wait(&barrier2);
    } else {
        for(int i = 0; i<3; i++){
            sem_post(&barrier2);
        }
    }

    printf("E\n");

    return NULL;
}

void *thread2(void *_arg) {
    args *threadArgs = _arg;

    pthread_mutex_lock(threadArgs->mutex);
    waiting++;
    pthread_mutex_unlock(threadArgs->mutex);

    printf("%d ",waiting);
    if(waiting < 4){
        sem_wait(&barrier);
    } else {
        for(int i = 0; i<3; i++){
            sem_post(&barrier);
        }
    }

    printf("B\n");

    pthread_mutex_lock(threadArgs->mutex);
    waiting2++;
    pthread_mutex_unlock(threadArgs->mutex);

    if(waiting2 < 4){
        sem_wait(&barrier2);
    } else {
        for(int i = 0; i<3; i++){
            sem_post(&barrier2);
        }
    }

    return NULL;
}

void *thread3(void *_arg) {
    args *threadArgs = _arg;

    pthread_mutex_lock(threadArgs->mutex);
    waiting++;
    pthread_mutex_unlock(threadArgs->mutex);

    if(waiting < 4){
        sem_wait(&barrier);
    } else {
        for(int i = 0; i<3; i++){
            sem_post(&barrier);
        }
    }

    printf("C\n");

    pthread_mutex_lock(threadArgs->mutex);
    waiting2++;
    pthread_mutex_unlock(threadArgs->mutex);

    if(waiting2 < 4){
        sem_wait(&barrier2);
    } else {
        for(int i = 0; i<3; i++){
            sem_post(&barrier2);
        }
    }

    return NULL;
}

void *thread4(void *_arg) {
    args *threadArgs = _arg;

    pthread_mutex_lock(threadArgs->mutex);
    waiting++;
    pthread_mutex_unlock(threadArgs->mutex);

    printf("%d ",waiting);
    if(waiting < 4){
        sem_wait(&barrier);
    } else {
        for(int i = 0; i<3; i++){
            sem_post(&barrier);
        }
    }

    printf("D\n");
    
    pthread_mutex_lock(threadArgs->mutex);
    waiting2++;
    pthread_mutex_unlock(threadArgs->mutex);

    if(waiting2 < 4){
        sem_wait(&barrier2);
    } else {
        for(int i = 0; i<3; i++){
            sem_post(&barrier2);
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t *threadIds = malloc(sizeof(pthread_t) * 4);
    args *threadArgs = malloc(sizeof(args) * 4);
    sem_init(&barrier, 0, 0);
    sem_init(&barrier2, 0, 0);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    void* (*functions[])(void*) = {thread1, thread2, thread3, thread4};

    // Crie TODAS as threads em um laço. Voce deve utilizar semaforos para sincronizacao.
    for(int i = 0; i<4; i++){
        threadArgs[i].mutex = &mutex;
        int status = pthread_create(&threadIds[i], NULL, functions[i], &threadArgs[i]);
    }

    // Espere por TODAS as threads
    for(int i = 0; i<4; i++){
        pthread_join(threadIds[i], NULL);
    }
    
    return 0;
}