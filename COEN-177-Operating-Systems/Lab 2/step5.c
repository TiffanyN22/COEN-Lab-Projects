// Name: Tiffany Nguyen
// Date: October 2, 2024
// Title: Lab 2 - Step 5: Create 7 processes (the original process, 2 child processes, and 2 child for each children).
// Each process prints its PID, its parent's PID, and its children's PID 

#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <errno.h> /* errno */
#include <sys/wait.h> 

int main(int argc, char *argv[]) {
    pid_t pid, pid2;
    int n = 500;
    int i;
    pid=fork();
    if(pid!=0) { //in parent
        pid2=fork();
        if(pid2 != 0){ //in parent
            printf("Current pid: %d | Parent Pid: %d | Child Pid: %d, %d\n\n", getpid(), getppid(), pid, pid2);
            wait(0);
        }
        else if(pid2 == 0) { // in child 2
            pid_t pid5, pid6;
            pid5=fork();
            if(pid5!=0) { //in child 2
                pid6=fork();
                if(pid6 != 0) { // in child 2
                    printf("Current pid: %d | Parent Pid: %d | Child Pid: %d, %d\n\n", getpid(), getppid(), pid5, pid6);
                    wait(0);
                } else if (pid6 == 0){ // in grandchid 2-2
                    printf("Current pid: %d | Parent Pid: %d | Child Pid %d \n\n", getpid(), getppid(), pid6);
                    wait(0);
                }
            } else if (pid5==0){ // in grandchild 2-1
                printf("Current pid: %d | Parent Pid: %d | Child Pid %d\n\n", getpid(), getppid(), pid5);
                wait(0);
            }
        }
    } else if (pid==0){ // in child 1
        pid_t pid3, pid4;
        pid3=fork();
        if(pid3!=0) { //in child 1
            pid4=fork();
            if(pid4 != 0) { // in child 1
                printf("Current pid: %d | Parent Pid: %d | Child Pid: %d, %d\n\n", getpid(), getppid(), pid3, pid4);
                wait(0);
            } else if (pid4 == 0){ // in grandchid 1-2
                printf("Current pid: %d | Parent Pid: %d | Child Pid %d\n\n", getpid(), getppid(), pid4);
                wait(0);
            }
        } else if (pid3==0){ // in grandchild 1-1
            printf("Current pid: %d | Parent Pid: %d | Child Pid %d\n\n", getpid(), getppid(), pid3);
            wait(0);
        }
    }
    return 0;
}