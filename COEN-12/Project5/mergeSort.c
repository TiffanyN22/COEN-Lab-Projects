/*
 * File Name: mergeSort.c
 * Author: Tiffany Nguyen
 * Date: November 18, 2022
 * Description: This file reads the data in data.txt, sorts the number column
 * in ascending order using merge sort, and prints out the sorted result
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_FILE_LENGTH 1000000
#define MAX_WORD_LENGTH 20

void mergeSort(int* elementsNum, char** elementsText, int size);
void mergeArrays(int* leftElementsNum, char** leftElementsText, int* rightElementsNum, char** rightElementsText, int* elementsNum, char** elementsText, int size);

int main(){
	FILE *data = fopen("data.txt", "r");
	if(data == NULL){
		printf("File failed to open");
	}
	assert(data != NULL);

        int* elementNum = malloc(sizeof(int) * MAX_FILE_LENGTH);
        char** elementText = malloc(sizeof(char*) *MAX_FILE_LENGTH);
        int i;
        for(i = 0; i< MAX_FILE_LENGTH; i++){
                elementText[i] = malloc(sizeof(char) * MAX_WORD_LENGTH);
        }

        int numOfElements = 0;
        while(!feof(data)){
          fscanf(data, "%d %s", &elementNum[numOfElements], elementText[numOfElements]);
          numOfElements++;
        }
        numOfElements--;
        printf("Num of Elements: %d\n", numOfElements);

        mergeSort(elementNum, elementText, numOfElements);

        //print out sorted values
        for(i = 0; i < numOfElements; i++){
        	printf("%d %s\n", elementNum[i], elementText[i]);
        }
}

/*
 * Function: mergeSort
 * Complexity: O(n logn)
 * Description: This function takes in 2 parallel arrays, elementsNum and elementsText,
 * and uses the merge sort algorithm to sort elementsNum is ascending order
 */
void mergeSort(int* elementsNum, char** elementsText, int size){
	assert(elementsNum != NULL && elementsText != NULL);
	//divide array
	if(size < 2){
		return;
	}
	int middle = size/2;
	
	//make left and right subarrays
	int* leftElementsNum = malloc(sizeof(int) * middle);
	char** leftElementsText = malloc(sizeof(char*) * middle);
	int i;
	for(i = 0; i < middle; i++){
		leftElementsText[i] = malloc(sizeof(char) * MAX_WORD_LENGTH);
	}
	for(i = 0; i < middle; i++){
		leftElementsNum[i] = elementsNum[i];
		leftElementsText[i] = elementsText[i];
	}

	int* rightElementsNum = malloc(sizeof(int) * (size-middle));
	char** rightElementsText = malloc(sizeof(char*) * (size-middle));	
	for(i = 0; i < (size-middle); i++){
		rightElementsText[i] = malloc(sizeof(char) * MAX_WORD_LENGTH);
	}
	for(i = middle; i < size; i++){
		rightElementsNum[i-middle] = elementsNum[i];
		rightElementsText[i-middle] = elementsText[i];
	}

	//recusively call to continue dividing array
	mergeSort(leftElementsNum, leftElementsText, middle);
	mergeSort(rightElementsNum, rightElementsText, size-middle);
	
	//call the merge subroutine to combine the 2 arrays and make them sorted
	mergeArrays(leftElementsNum, leftElementsText, rightElementsNum, rightElementsText, elementsNum, elementsText, size);
}

/*
 * Function: mergeArrays
 * Complexity: O(n)
 * Description: This function is the merge subroutine of mergeSort. It takes in 2 sorted arrays
 * for the elements' numbers and text and combines them in the passed in elementsNum and 
 * elementsText arrays so that elementsNum is in ascending order.
 */
void mergeArrays(int* leftElementsNum, char** leftElementsText, int* rightElementsNum, char** rightElementsText, int* elementsNum, char** elementsText, int size){
	assert(leftElementsNum != NULL && leftElementsText != NULL);
	assert(rightElementsNum != NULL && rightElementsText != NULL);
	assert(elementsNum != NULL && elementsText != NULL);

	int leftArrayLength = size/2;
	int rightArrayLength = size - (size/2);

	int leftCounter = 0;
	int rightCounter = 0;
	int arrayCounter = 0;
	
	while((leftCounter < leftArrayLength) && (rightCounter < rightArrayLength)){
		if(leftElementsNum[leftCounter] <= rightElementsNum[rightCounter]){
			elementsNum[arrayCounter] = leftElementsNum[leftCounter];
			elementsText[arrayCounter] = leftElementsText[leftCounter];
			leftCounter++;
		}
		else{
			elementsNum[arrayCounter] = rightElementsNum[rightCounter];
			elementsText[arrayCounter] = rightElementsText[rightCounter];
			rightCounter++;
		}
		arrayCounter++;
	}
	while(leftCounter < leftArrayLength){
		elementsNum[arrayCounter] = leftElementsNum[leftCounter];
		elementsText[arrayCounter] = leftElementsText[leftCounter];
		leftCounter++;
		arrayCounter++;
	}
	while(rightCounter < rightArrayLength){
		elementsNum[arrayCounter] = rightElementsNum[rightCounter];
		elementsText[arrayCounter] = rightElementsText[rightCounter];
		rightCounter++;
		arrayCounter++;
	}
}
