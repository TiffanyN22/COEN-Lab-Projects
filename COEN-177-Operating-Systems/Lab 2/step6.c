// Name: Tiffany Nguyen
// Date: October 2, 2024
// Title: Lab 2 - Step 6: Run 2 threads that print out 0 to 99 in parallel

#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <errno.h> /* errno */
#include <sys/wait.h> 
#include <stdlib.h> /* atoi */
#include <pthread.h>
#include <stdint.h>

void* childThread(void* vargp)
{
    int i;
    int n = (intptr_t)vargp; // cast parameter to get delay

    for (i=0;i<100;i++) { // print 0 to 99
        printf("Child process %d\n",i);
        usleep(n);
    }
}

int main(int argc, char *argv[]) {
    int i, n = atoi(argv[1]); // n microseconds delay from argv input
    printf("\n Before forking.\n");

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, childThread, (void*)(intptr_t)n); // create child thread to run simultaneously

    // run parent process to print 0 to 99
    for (i=0;i<100;i++) {
        printf("\t \t \t Parent Process %d \n",i);
        usleep(n);
    }

    pthread_join(thread_id, NULL);

    return 0;
}
