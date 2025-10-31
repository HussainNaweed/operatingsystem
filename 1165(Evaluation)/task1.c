/*  Create a shared global variable

2.  Create 4 threads:

Thread 1: Deposits 1000 (repeat 5 times)

Thread 2: Withdraws 500 (repeat 5 times)

  Thread 3: Deposits 800 (repeat 5 times)

  Thread 4: Withdraws 300 (repeat 5 times)

3.  Use mutex to protect balance updates

4.  Each thread should print after each transaction:   Thread ID

  Operation (Deposit/Withdraw)   Amount


initialized to 5000

  New balance
  Main thread print final balence
  */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int balance = 5000;       //shared global variables    
pthread_mutex_t lock;          // Mutex for synchronization
//Prevents two threads from updating balence at the same time
void* deposit(void* arg) {  //deposit function for thread that add money
    int amount = *(int*)arg; //Amount to deposit
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);  // lock before updating balence
        balance += amount; //Add deposit amount
        printf("Thread %lu: Deposit %d | New Balance: %d\n",
               pthread_self(), amount, balance);
        pthread_mutex_unlock(&lock); // unlock after update
        sleep(1);// small delay
    }
    return NULL;
}

void* withdraw(void* arg) { // Withdraw function for threads that remove money
    int amount = *(int*)arg; // Amount to withdraw
    for (int i = 0; i < 5; i++) { // Repeat 5 times
        pthread_mutex_lock(&lock);
        if (balance >= amount) { // Check if enough balence
            balance -= amount; // Substract Withdraw a,ount
            printf("Thread %lu: Withdraw %d | New Balance: %d\n",
                   pthread_self(), amount, balance);
        } else {
            printf("Thread %lu: Withdraw %d | Failed (Insufficient funds)\n",
                   pthread_self(), amount);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;

    int dep1 = 1000; //Deposit amount for thread1
    int with1 = 500; //Withdraw amount for thread2
    int dep2 = 800;  //Deposit amount for thread3
    int with2 = 300; //Withdraw amount for thread 3

    pthread_mutex_init(&lock, NULL);

    printf("Initial Balance: %d\n", balance);

    pthread_create(&t1, NULL, deposit, &dep1);
    pthread_create(&t2, NULL, withdraw, &with1);
    pthread_create(&t3, NULL, deposit, &dep2);
    pthread_create(&t4, NULL, withdraw, &with2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
// Wait for all threads to finish
    printf("Final Balance: %d\n", balance);
// Print all the balence after transactions
    pthread_mutex_destroy(&lock);
    return 0;
}