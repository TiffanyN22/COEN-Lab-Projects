// Name: Tiffany Nguyen
// Date: November 13, 2024
// Title: Lab 8 - LRU
// Description: The file gets number from the inputBuffer and handles page replacement using LRU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    int timeSinceUse;
} ref_page;


int main(int argc, char *argv[]){
    int cacheSize = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[cacheSize]; // Virtual cache for simulator 
    char inputBuffer[100]; // Buffer to hold input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int placeInArray = 0; // keep track of where in cache to add

    for (i = 0; i < cacheSize; i++){//initialise cache array  
         cache[i].pageno = -1;
         cache[i].timeSinceUse = 0;
    }

    while (fgets(inputBuffer, 100, stdin)){
    	int page_num = atoi(inputBuffer); // Stores number read from file as an int

        // update time since use for all elements in cache
        for (i = 0; i < cacheSize; i++){ //initialise cache array  
            if(cache[i].pageno != -1) { // if in use
                cache[i].timeSinceUse++;
            }
        }

        // set timeSinceUse to 0 if the value is in the cache
        bool foundInCache = false;
        for (i=0; i<cacheSize; i++){
            if (cache[i].pageno == page_num){
                foundInCache = true;
                cache[i].timeSinceUse = 0;
                break; //break out loop because found page_num in cache
            }
        }

        if (foundInCache == false){
            //Print the page that caused the page fault
            printf("Page fault in %d\n", page_num);
            totalFaults++; 
            
            if(placeInArray < cacheSize){ // if cache not filled, add it to the cache at the end
                cache[placeInArray].pageno = page_num;
                placeInArray++;
            } else { // if cache is filled - use lru to determine what to replace
                int oldestIndex = 0;
                for (i = 0; i < cacheSize; i++){
                    if(cache[i].timeSinceUse > cache[oldestIndex].timeSinceUse) { // if older
                        oldestIndex = i;
                    }
                }
                cache[oldestIndex].pageno = page_num;
                cache[oldestIndex].timeSinceUse = 0;
            }
        }
    }

    return 0;
}
