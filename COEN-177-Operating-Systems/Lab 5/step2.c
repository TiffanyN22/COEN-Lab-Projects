// Name: Tiffany Nguyen
// Date: October 23, 2024
// Title: Lab 5 - Part 2
// Description: This program modifies the provided Thread Sychronization program to 
// use mutexes to create 10 threads and make each thread wait until the critical section 
// is unlocked.
//To compile this code: gcc step2.c -o step2 -lpthread

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock; 

void* go(void* arg) { 
    pthread_mutex_lock(&lock);
    printf("Thread %d Entered Critical Section..\n", (int)(size_t)arg); //critical section 
    sleep(1); 
    pthread_mutex_unlock(&lock); //exit section 
    return (NULL);
} 

int main() { 
    pthread_mutex_init(&lock, NULL);
    static int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
        printf("\t\t\tThread %d returned \n", i);
    }
    printf("Main thread done.\n");
    pthread_mutex_destroy(&lock);
    return 0; 
} 
