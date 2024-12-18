// Name: Tiffany Nguyen
// Date: October 23, 2024
// Title: Lab 5 - Part 3
// Description: This program solves the producer-consumer program using semaphores

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <stdlib.h>

#define N 10

pthread_t threads[2];
int buffer[N];
int inIndex, outIndex;

sem_t *fullSem;
sem_t *emptySem;
sem_t *lockSem;

void* producer(void* arg) { 
    srand(time(NULL));    
    do {
        // produce item
        int item =  rand() % 100; 
        printf("Producing %d\n", item);

        // wait empty
        sem_wait(emptySem);

        // wait lock
        sem_wait(lockSem);

        // add item to buffer
        buffer[inIndex] = item;
        inIndex = (inIndex + 1) % N;

        // signal lock
        sem_post(lockSem);

        // signal full
        sem_post(fullSem);

        sleep(1);
    } while(1);
    return (NULL);
} 

void* consumer(void* arg) { 
    do {
        // wait full
        sleep(1);
        sem_wait(fullSem);

        // wait lock;
        sem_wait(lockSem);

        int nextItem = buffer[outIndex];
        outIndex = (outIndex + 1) % N;
        
        // signal lock
        sem_post(lockSem);

        // signal empty
        sem_post(emptySem);

        // "consume" by printing
        printf("        Consuming %d\n", nextItem);
    } while(1);
    return (NULL);
} 

int main() { 
    inIndex = 0;
    outIndex = 0;

    // initialize semaphores
    fullSem = sem_open("full", O_CREAT, 0644, 0);
    emptySem = sem_open("empty", O_CREAT, 0644, N);
    lockSem = sem_open("lock", O_CREAT, 0644, 1);

    // create producer and consumer threads
    pthread_create(&threads[0], NULL, producer, NULL);
    pthread_create(&threads[1], NULL, consumer, NULL);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);

    printf("Main thread done.\n");

    sem_unlink("full"); 
    sem_unlink("empty"); 
    sem_unlink("lock"); 
    return 0; 
} 
