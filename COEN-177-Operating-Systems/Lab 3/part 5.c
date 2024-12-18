// Name: Tiffany Nguyen
// Date: October 9, 2024
// Title: Lab 3 - Part 5
// Description: The producer generates a message in a loop and the consumer prints it out.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
    int  fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    
    if (fork()==0){ // producer
        dup2(fds[0], 0); // duplicate upstream file descriptor
        close(fds[1]); // close downstream pipe
        
        int i;
        char message[50];
        
        while(read(fds[0], message, sizeof(message)) > 0){
            printf(message);
            printf("\n");
        }
        
        exit(0);
    }
    else if(fork()==0){ // consumer
        dup2(fds[1], 1); // duplicate downstream file descriptor
        close(fds[0]); // close upstream pipe

        char message[50];
        for(i=0; i<INT_MAX; i++){
            sprintf(message, "Message %d", i);
            //printf("Producing %s\n", message);
            write(fds[1], message, sizeof(message));
        }
        
        exit(0);
    }
    else{     
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}