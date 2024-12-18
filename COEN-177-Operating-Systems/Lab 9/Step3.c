// Name: Tiffany Nguyen
// Date: November 13, 2024
// Title: Lab 8 - Part 2
// Description: The program reads the passed in file using the passed in buffer size.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) { 
    int bufferSize = atoi(argv[2]);
    char buffer[bufferSize];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    while(fread(buffer, sizeof(buffer), 1, fp)){

    }
    return 0;
}