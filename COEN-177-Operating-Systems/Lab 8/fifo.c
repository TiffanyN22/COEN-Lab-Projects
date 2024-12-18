// Name: Tiffany Nguyen
// Date: November 13, 2024
// Title: Lab 8 - FIFO
// Description: The file gets number from the inputBuffer and handles page replacement using FIFO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
    int cacheSize = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[cacheSize]; // Virtual cache for simulator 
    char inputBuffer[100]; // Buffer to hold input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults

    int placeInArray = 0;
    
    for (i = 0; i < cacheSize; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(inputBuffer, 100, stdin)){
    	int page_num = atoi(inputBuffer); // Stores number read from file as an int

        bool foundInCache = false;
        for (i=0; i<cacheSize; i++){
            if (cache[i].pageno == page_num){
                foundInCache = true;
                break; //break out loop because found page_num in cache
            }
        }
        if (foundInCache == false){
            //You may print the page that caused the page fault
            printf("Page fault in %d\n", page_num);
            cache[placeInArray].pageno = page_num;
            totalFaults++;
            placeInArray = (placeInArray+1) % cacheSize; //Need to keep the value within the cacheSize
        }
    }

    return 0;
}
