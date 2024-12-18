// Name: Tiffany Nguyen
// Date: November 13, 2024
// Title: Lab 8 - Part 2
// Description: The program reads the passed in file.

#include <stdio.h>

int main(int argc, char *argv[]) { 
    char buffer[10000];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    while(fread(buffer, sizeof(buffer), 1, fp)){

    }
    return 0;
}