#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define STATIONS 2
#define CARS 6

sem_t wash;

void* car(void* arg) {
    int id = *(int*)arg;

    sem_wait(&wash);
    printf("Car %d is being washed\n", id);

    sleep(3);

    printf("Car %d finished washing\n", id);
    sem_post(&wash);

    return NULL;
}

int main() {
    pthread_t c[CARS];
    int ids[CARS];

    sem_init(&wash, 0, STATIONS);

    for(int i = 0; i < CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&c[i], NULL, car, &ids[i]);
    }

    for(int i = 0; i < CARS; i++)
        pthread_join(c[i], NULL);

    sem_destroy(&wash);
    return 0;
}