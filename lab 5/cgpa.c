#include <stdio.h>
 #include <pthread.h>
 void* print_number(void* arg) {
// We know that we've passed an integer pointer
 float num = *(float*)arg; // Cast void* back to int*
 printf("Thread received number: %f\n", num);
 printf("Square: %f\n", 2 * num);
 return NULL;
 }
 int main() {
 pthread_t thread_id;
 float number = 2.8;
 printf("Creating thread with argument: %f\n", number);
 // Pass address of 'number' to thread
 pthread_create(&thread_id, NULL, print_number, &number);
 pthread_join(thread_id, NULL);
 printf("Main thread done.\n");
 return 0;
 }