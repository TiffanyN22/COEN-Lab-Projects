// Name: Tiffany Nguyen
// Date: October 2, 2024
// Title: Lab 2 - Step 7: Parent process spawns child process to run a separate program to
// run ls command and display all files in the current directory

#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <errno.h> /* errno */
#include <sys/wait.h> 
#include <stdlib.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    pid=fork(); // create process
    if(pid == 0) // in child
    {
        execlp("/bin/ls", "ls", NULL); // run ls command
    }
    else
    {
        wait(NULL);
        printf("Child Complete");
        exit(0);
    }
    return 0;
}