// Name: Tiffany Nguyen
// Date: November 13, 2024
// Title: Lab 8 - Part 2
// Description: The program creates argv[3] threads, where each thread reads the passed in file at argv[1] using the buffer
// size passed in at argv[2] and copies the file's contents into copy#.out, where # is the thread number

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char inputFileName[50];
int bufferSize;

void *threadReadWriteFile(void *arg) {
    int threadNum = *(int *) arg;
    
    char buffer[bufferSize];

    char fileName[50];
    sprintf(fileName, "copy%d.out", threadNum);
    
    FILE *fpWrite;
    fpWrite = fopen(fileName, "wb");

    FILE *fp;
    fp = fopen(inputFileName, "rb");
    while(fread(buffer, sizeof(buffer), 1, fp)){
        fwrite(buffer, 1, sizeof(buffer), fpWrite);
    }

    fclose(fp);
    fclose(fpWrite);
    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    strcpy(inputFileName, argv[1]);
    bufferSize = atoi(argv[2]);
    int numThreads = atoi(argv[3]);

    pthread_t thread[numThreads];

    int i;
    for (i=0; i < numThreads; i++){

        int *arg = malloc(sizeof(int*));
        *arg = i;
            
        if(pthread_create(&thread[i], NULL, threadReadWriteFile, (void *)arg) != 0){
            printf("pthread_create fails on %d\n", i);
            return 0;
        }
    }
    int j;
    for (j=0; j < numThreads; j++){
        pthread_join(thread[j],NULL);
    }
    
    return 0;
}
