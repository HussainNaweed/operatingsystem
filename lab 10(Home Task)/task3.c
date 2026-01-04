#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define COMPUTERS 4
#define STUDENTS 8

sem_t computers;
pthread_mutex_t mutex;
int occupied = 0;

void* student(void* arg) {
    int id = *(int*)arg;

    sem_wait(&computers);

    pthread_mutex_lock(&mutex);
    occupied++;
    printf("Student %d entered | Occupied: %d\n", id, occupied);
    pthread_mutex_unlock(&mutex);

    sleep(rand() % 3 + 1);

    pthread_mutex_lock(&mutex);
    occupied--;
    printf("Student %d left | Occupied: %d\n", id, occupied);
    pthread_mutex_unlock(&mutex);

    sem_post(&computers);
    return NULL;
}

int main() {
    pthread_t s[STUDENTS];
    int ids[STUDENTS];

    sem_init(&computers, 0, COMPUTERS);
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < STUDENTS; i++) {
        ids[i] = i + 1;
        pthread_create(&s[i], NULL, student, &ids[i]);
    }

    for(int i = 0; i < STUDENTS; i++)
        pthread_join(s[i], NULL);

    sem_destroy(&computers);
    pthread_mutex_destroy(&mutex);
    return 0;
}