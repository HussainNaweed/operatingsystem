#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CARS 3
#define TOTAL_CARS 8

sem_t bridge;
pthread_mutex_t print;

void* car(void* arg) {
    int id = *(int*)arg;
    int time = rand() % 3 + 1;

    sem_wait(&bridge);

    pthread_mutex_lock(&print);
    printf("Car %d entered bridge\n", id);
    pthread_mutex_unlock(&print);

    sleep(time);

    pthread_mutex_lock(&print);
    printf("Car %d left bridge\n", id);
    pthread_mutex_unlock(&print);

    sem_post(&bridge);
    return NULL;
}

int main() {
    pthread_t c[TOTAL_CARS];
    int ids[TOTAL_CARS];

    sem_init(&bridge, 0, MAX_CARS);
    pthread_mutex_init(&print, NULL);

    for(int i = 0; i < TOTAL_CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&c[i], NULL, car, &ids[i]);
    }

    for(int i = 0; i < TOTAL_CARS; i++)
        pthread_join(c[i], NULL);

    sem_destroy(&bridge);
    pthread_mutex_destroy(&print);
    return 0;
}