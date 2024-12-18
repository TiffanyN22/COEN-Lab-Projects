// Name: Tiffany Nguyen
// Date: October 16, 2024
// Title: Lab 4 - Part 3
// Description: This program uses multithreading to perform matrix multiplication, where each thread
// will calculate the result for one row of the output matrix

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


// define size of matrix
#define N 1500 // number of columns in matrix A
#define M 1024 // number of rows in matrix A and columns in matrix B
#define L 1200 // number of rows in matrix B

void *multiplyOneRow(void *);
pthread_t threads[N];

// declare global matricies
// size (set in main): matrixA[N][M], matrixB[M][L], matrixC[N][L];
double** matrixA;
double** matrixB;
double** matrixC;

int main() {
    // randomly initialize and print values of matrix A and B
    printf("Matrix A:\n");
    srand(time(NULL));
    matrixA = (double**)malloc(sizeof(double*)*N); // dynamically initialize 2d array
    for (int i = 0; i < N; i++){
        matrixA[i] = (double*)malloc(sizeof(double)*M);
        for (int j = 0; j < M; j++){
            matrixA[i][j] = rand(); //randomly assign value
            printf("%.2f ", matrixA[i][j]); // print
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    srand(time(NULL));
    matrixB = (double**)malloc(sizeof(double*)*M);
    for (int i = 0; i < M; i++){
        matrixB[i] = (double*)malloc(sizeof(double)*L);
        for (int j = 0; j < L; j++){
            matrixB[i][j] = rand();
            printf("%.2f ", matrixB[i][j]);
        }
        printf("\n");
    }

    // malloc for matrixC
    matrixC = (double**)malloc(sizeof(double*)*N);
    for (int i = 0; i < N; i++){
        matrixC[i] = (double*)malloc(sizeof(double)*L);
    }

    // use multithreading to calculate each row in matrix c
    for (int i = 0; i < N; i++){
        int *arg = malloc(sizeof(int*));
        *arg = i;
        if(pthread_create(&threads[i], NULL, multiplyOneRow, (void *)arg) != 0){
            printf("pthread_create fails on %d", i);
            return 0;
        }
    }

    // make main thread wait for all threads to complete before displaying result
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i],NULL);
    }

    // display result
    printf("\nResult Matrix C:\n");
    for (int i = 0; i < N; i++){
        for(int j = 0; j< L; j++){
            printf("%.2f ", matrixC[i][j]);
        }
        printf("\n");
    }

    // free storage
    for(int i = 0; i < N; i++){
        free(matrixA[i]);
    }
    free(matrixA);
    for(int i = 0; i < M; i++){
        free(matrixB[i]);
    }
    free(matrixB);
    for(int i = 0; i < N; i++){
        free(matrixC[i]);
    }
    free(matrixC);

    printf("Main thread done.\n");
}

void *multiplyOneRow(void *arg) {
    // IArg* iArg = (IArg*)arg;// cast parameter to struct to know which row of c
    int i = *(int *) arg;
    free(arg); 
    for (int j = 0; j < L; j++){ // iterate through each row of B 
        double temp = 0;
        for (int k = 0; k < M; k++){ // iterate each each column of A for given row
            temp += matrixA[i][k] * matrixB[k][j];
        }
        matrixC[i][j] = temp;
    }
    return (NULL);
}
