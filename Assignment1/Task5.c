

#include <stdio.h>
#include <pthread.h>
#include <string.h>

// Define Student structure
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

int dean_count = 0;
pthread_mutex_t lock; // Mutex for safe counter update

// Thread function
void* check_deans_list(void* arg) {
    Student* s = (Student*)arg;

    printf("Student ID: %d\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("GPA: %.2f\n", s->gpa);

    // Check eligibility for Dean’s List
    if (s->gpa >= 3.5) {
        printf("Status: Eligible for Dean's List \n\n");
        pthread_mutex_lock(&lock);
        dean_count++;
        pthread_mutex_unlock(&lock);
    } else {
        printf("Status: Not eligible for Dean's List \n\n");
    }

    return NULL;
}

int main() {
    pthread_t threads[3];
    Student students[3] = {
        {101, "Haider Ali", 3.2},
        {102, "Kashmir", 3.8},
        {103, "Hassan", 3.9}
    };

    pthread_mutex_init(&lock, NULL);

    // Create 3 threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, check_deans_list, &students[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: Total students on Dean's List = %d\n", dean_count);

    pthread_mutex_destroy(&lock);
    return 0;
}
