// Name: Tiffany Nguyen
// Date: October 9, 2024
// Title: Lab 3 - Part 4
// Description: This program prints out the same output as cat /etc/passwd|grep root

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
    int  fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    
    if (fork()==0){
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("grep", "grep", "root", 0); //call grep root with output of cat /etc/passwd
        
        exit(0);
    }
    else if(fork()==0){ 
        dup2(fds[1], 1);
        close(fds[0]);
         execlp("cat", "cat", "/etc/passwd", 0); //call cat /etc/passwd and put in pipe
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
