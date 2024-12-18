// Name: Tiffany Nguyen
// Date: October 9, 2024
// Title: Lab 3 - Part 3
// Description: This program prints out the output of the ls command with spaces between all letters

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
   
   if (fork()==0){ //upstream pipe
       dup2(fds[1], 1); // duplicate upstream file descriptor
       close(fds[0]); // close downstream pipe
       execlp("ls", "ls", 0); 
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]); // close upstream pipe
       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);
               write(1," ",1); // space between letters
           }
           printf("\n");
       }
       exit(0);
    }
   else{  
        // in parent: close both upstream and downstream, wait  
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
   }
return 0;
}
