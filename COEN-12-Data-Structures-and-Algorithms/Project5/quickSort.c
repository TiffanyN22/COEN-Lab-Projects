/*
 * File Name: quickSort.c
 * Author: Tiffany Nguyen
 * Date: November 23, 2022
 * Description: This file reads the data in data.txt (the file it reads it hard-
 * coded, but can be changed), sorts the number column in ascending order
 * using the quickSort algorithm, and prints out the sorted result, including
 * both the number and text column.
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_FILE_LENGTH 1000000
#define MAX_WORD_LENGTH 20

int partition(int* elementsNum, char** elementsText, int startIndex, int endIndex);
void quickSort(int* elementsNum, char** elementsText, int startIndex, int endIndex);

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

        quickSort(elementNum, elementText, 0, numOfElements -1);

        //print out sorted values
        for(i = 0; i < numOfElements; i++){
        	printf("%d %s\n", elementNum[i], elementText[i]);
        }
}

/*
 * Function: partition
 * Complexity: O(n)
 * Description: This function is the parition subroutine of quicksort, which will
 * select the element at endIndex to be the pivot and sort the elementsNum array so
 * that, by the end, all elements between startIndex and the pivot are less than the 
 * pivot and all elements between pivot and endIndex are greater than pivot. Since 
 * elementsText is a parallel array to elementsNum, it will also swap and sort its
 * values accordingly.
 */
int partition(int* elementsNum, char** elementsText, int startIndex, int endIndex){
	assert(elementsNum != NULL && elementsText != NULL);
	int pivot = elementsNum[endIndex];
	int pivotIndex = startIndex;
	int i;
	for(i = startIndex; i < endIndex; i++){
		if(elementsNum[i] <= pivot){
			//swap
			int tempNum = elementsNum[i];
			elementsNum[i] = elementsNum[pivotIndex];
			elementsNum[pivotIndex] = tempNum;
			char* tempText = malloc(sizeof(char) * MAX_WORD_LENGTH);
			tempText = elementsText[i];
			elementsText[i] = elementsText[pivotIndex];
			elementsText[pivotIndex] = tempText;

			pivotIndex++;
		}
	}
	
	//swap to put pivot in its position
	int tempNum = elementsNum[pivotIndex];
	elementsNum[pivotIndex] = elementsNum[endIndex];
	elementsNum[endIndex] = tempNum;
	char* tempText = malloc(sizeof(char) * MAX_WORD_LENGTH);
	tempText = elementsText[pivotIndex];
	elementsText[pivotIndex] = elementsText[endIndex];
	elementsText[endIndex] = tempText;
	
	return pivotIndex;	
}

/*
 * Function: quickSort
 * Complexity: O(n^2) worst case, O(n logn) expected
 * Description: This function sorts elementsNum in ascending order using the 
 * quicksort algorithm by calling the partition function and recursively calling 
 * quicksort for each half of the array
 */
void quickSort(int* elementsNum, char** elementsText, int startIndex, int endIndex){
	assert (elementsNum != NULL && elementsText != NULL);
	if(startIndex >= endIndex){
		return;
	}
	int pivotIndex = partition(elementsNum, elementsText, startIndex, endIndex);
	quickSort(elementsNum, elementsText, startIndex, pivotIndex - 1);
	quickSort(elementsNum, elementsText, pivotIndex + 1, endIndex);

}
