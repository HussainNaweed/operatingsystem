#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_DOWNLOADS 3
#define TOTAL_FILES 8

sem_t download_slots;

void* download(void* arg) {
    int id = *(int*)arg;
    int time = rand() % 5 + 1;

    sem_wait(&download_slots);
    printf("Download %d started (%d sec)\n", id, time);

    sleep(time);

    printf("Download %d finished\n", id);
    sem_post(&download_slots);

    return NULL;
}

int main() {
    pthread_t files[TOTAL_FILES];
    int ids[TOTAL_FILES];

    sem_init(&download_slots, 0, MAX_DOWNLOADS);

    for(int i = 0; i < TOTAL_FILES; i++) {
        ids[i] = i + 1;
        pthread_create(&files[i], NULL, download, &ids[i]);
    }

    for(int i = 0; i < TOTAL_FILES; i++)
        pthread_join(files[i], NULL);

    sem_destroy(&download_slots);
    return 0;
}