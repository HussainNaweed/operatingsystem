


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* greet(void* arg) {
    char* name = (char*)arg;
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    char* userName = "Haider Ali";

    printf("Main thread: Waiting for greeting...\n");
    pthread_create(&thread, NULL, greet, (void*)userName);
    pthread_join(thread, NULL);
    printf("Main thread: Greeting completed.\n");

    return 0;
}