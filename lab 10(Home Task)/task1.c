#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define ROOMS 3
#define PEOPLE 8

sem_t rooms;

void* person(void* arg) {
    int id = *(int*)arg;

    printf("Person %d is waiting for a room...\n", id);
    sem_wait(&rooms);

    printf("Person %d got a room.\n", id);
    sleep(2);

    printf("Person %d left the room.\n", id);
    sem_post(&rooms);

    return NULL;
}

int main() {
    pthread_t p[PEOPLE];
    int ids[PEOPLE];

    sem_init(&rooms, 0, ROOMS);

    for(int i = 0; i < PEOPLE; i++) {
        ids[i] = i + 1;
        pthread_create(&p[i], NULL, person, &ids[i]);
    }

    for(int i = 0; i < PEOPLE; i++)
        pthread_join(p[i], NULL);

    sem_destroy(&rooms);
    return 0;
}