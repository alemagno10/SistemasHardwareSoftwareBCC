#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

// linha de compilação: 

/* declarar tarefas aqui e lançar no main */
/* cada bloco na figura deverá ser representado por um print com sua letra */

typedef struct {
    char before;
    char after;
    pthread_mutex_t *mutex;
} args;

sem_t sem_barrier1;
sem_t sem_barrier2;
int bar1 = 0;
int bar2 = 0;

void *printChar(void *arg) {
    args *threadArgs = arg;

    sem_wait(threadArgs->barrier); // Aguarda a liberação da barreira anterior

    printf("%c\n", threadArgs->before);

    if (threadArgs->before == 'a' || threadArgs->before == 'b') {
        if (bar1 == 0) {
            pthread_mutex_lock(threadArgs->mutex);
            bar1++;
            pthread_mutex_unlock(threadArgs->mutex);
            sem_post(threadArgs->barrier); // Libera a barreira atual
        }
    } else if (threadArgs->before == 'b' || threadArgs->before == 'c' || threadArgs->before == 'd') {
        if (bar2 < 4) {
            pthread_mutex_lock(threadArgs->mutex);
            bar2++;
            pthread_mutex_unlock(threadArgs->mutex);
            sem_post(threadArgs->barrier); // Libera a barreira atual
        }
    }

    printf("%c\n", threadArgs->after);
    pthread_exit(NULL);
}

int main() {
    int N = 4;
    pthread_t *threadIds = malloc(sizeof(pthread_t) * N);
    args *threadArgs = malloc(sizeof(args) * N);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    char before[4] = {'a', 'b', 'e', 'g'};
    char after[4] = {'c', 'd', 'f', 'h'};

    for (int i = 0; i < 4; i++) {
        threadArgs[i].before = before[i];
        threadArgs[i].after = after[i];
        threadArgs[i].mutex = &mutex;
        int status = pthread_create(&threadIds[i], NULL, printChar, &threadArgs[i]);
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
