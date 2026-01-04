#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define WORKERS 3
#define TASKS 10

sem_t workers;

void* task(void* arg) {
    int id = *(int*)arg;

    sem_wait(&workers);
    printf("Task %d is running\n", id);

    sleep(rand() % 2 + 1);

    printf("Task %d finished\n", id);
    sem_post(&workers);

    return NULL;
}

int main() {
    pthread_t t[TASKS];
    int ids[TASKS];

    sem_init(&workers, 0, WORKERS);

    for(int i = 0; i < TASKS; i++) {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, task, &ids[i]);
    }

    for(int i = 0; i < TASKS; i++)
        pthread_join(t[i], NULL);

    sem_destroy(&workers);
    return 0;
}