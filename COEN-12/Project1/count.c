/*
 * File name: count.c
 * Author: Tiffany Nguyen
 * Date: September 23, 2022
 * Description: Counts the number of words in a paseed in file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 30

int main(int argc, char ** argv){
	//Checks to make sure file is passed in
	if(argc != 2){
		printf("Missing file name");
		return 0;
	}
	
	//opens the passed in file
	FILE *file = fopen(argv[1], "r");
	if(file == NULL){
		printf("Could not open file");
		return 0;
	}
	
	//counts the number of words in the file
	char scannedWord[MAX_WORD_LENGTH];
	int totalWords = 0;
	while(fscanf(file, "%s", scannedWord) == 1){
		totalWords++;
	}
	printf("There are %d words in total", totalWords);
	
	//closes the file
	fclose(file);
	return 0;
}
