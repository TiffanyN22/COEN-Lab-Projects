/*
 * File Name: insertionSort.c
 * Author: Tiffany Nguyen
 * Date: November 11, 2022
 * Description: This file reads the data in data.txt, sorts the number column in ascending
 * order, and prints out the sorted result using insertion sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_FILE_LENGTH 1000000
#define MAX_WORD_LENGTH 20

void insertionSort(int* elementsNum, char** elementsText,  int size);

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
	printf("%d\n", numOfElements);	
	
	insertionSort(elementNum, elementText, numOfElements); 
	
	//print out sorted values
	for(i = 0; i < numOfElements; i++){
		printf("%d %s\n", elementNum[i], elementText[i]);
	}
	
}

/*
 * Function: insertionSort
 * Complexity: O(n^2)
 * Description: This function takes in two parallel arrays representing a number and its 
 * corresponding string, along with its size, and sorts the 2 array so that elementsNum
 * is in ascending order using insertionSort 
 */
void insertionSort(int* elementsNum, char** elementsText,  int size){
	assert(elementsNum != NULL && elementsText != NULL);
	int i;
	for (i = 1; i < size; i++){
		int currentElementNum = elementsNum[i];
		char* currentElementText = malloc(sizeof(char) * MAX_WORD_LENGTH);
	 	currentElementText = elementsText[i];
		
		int j = i;
		while ((j >= 1) && (elementsNum[j-1] > currentElementNum)){
			elementsNum[j] = elementsNum[j-1];
			elementsText[j] = elementsText[j-1];
			j--;
		}
		elementsNum[j] = currentElementNum;
		elementsText[j] = currentElementText;
	}
}
