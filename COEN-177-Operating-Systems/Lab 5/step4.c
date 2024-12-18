// Name: Tiffany Nguyen
// Date: October 23, 2024
// Title: Lab 5 - Part 4
// Description: This program solves the producer-consumer program using a
// mutex lock and conditional variables

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
int bufferFilled;

pthread_mutex_t lock; // mutex lock
pthread_cond_t full; // full conditional variable
pthread_cond_t empty; // empty conditional variable

void* producer(void* arg) { 
    srand(time(NULL));    
    do {
        // produce next item
        int item =  rand() % 100; 
        printf("Producing %d\n", item);

        // lock
        pthread_mutex_lock(&lock);

        while(bufferFilled == N){ // while buffer is full
            pthread_cond_wait(&empty, &lock);
        }

        // add item to buffer
        buffer[inIndex] = item;
        inIndex = (inIndex + 1) % N;
        bufferFilled++;

        // signal conditional variable
        pthread_cond_signal(&full);

        // unlock
        pthread_mutex_unlock(&lock);

        sleep(1);
    } while(1);
    return (NULL);
} 

void* consumer(void* arg) { 
    do {
        // lock
        pthread_mutex_lock(&lock);

        while(bufferFilled == 0){ // while buffer is empty
            pthread_cond_wait(&full, &lock);
        }


        // remove next item
        if(inIndex == outIndex) {
            sleep(1);
            continue;
        }
        int nextItem = buffer[outIndex];
        outIndex = (outIndex + 1) % N;
        bufferFilled--;
        
        // signal conditional variable
        pthread_cond_signal(&empty);

        // unlock
        pthread_mutex_unlock(&lock);

        // "consume" by printing
        printf("        Consuming %d\n", nextItem);
        sleep(1);
    } while(1);
    return (NULL);
} 

int main() { 
    // initialize mutex and conditional variable
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    inIndex = 0;
    outIndex = 0;
    bufferFilled = 0;

    // create producer and consumer threads
    pthread_create(&threads[0], NULL, producer, NULL);
    pthread_create(&threads[1], NULL, consumer, NULL);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);

    printf("Main thread done.\n");
    pthread_mutex_destroy(&lock); // destroy mutex

    return 0; 
} 
