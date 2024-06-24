/*
* Name: Tiffany Nguyen
* Date: April 17, 2024
* Title: Lab 3 - Part 2
* Description: TCP client requesting a file transfer from the server.
* The client will send a file name, read the data from the file from the server,
* and store the read data inside of a new destinatino file.
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>
#include <strings.h>

//for reading/writing with system
#include <sys/mman.h> // mmap()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 10 //buffer size

int main(int argc, char *argv[]){
    //Get from the command line, server IP, src and dst files.
    if (argc != 5){
		printf ("Usage: %s <ip of server> <port #> <src_file> <dest_file>\n",argv[0]);
		exit(0);
    } 

    //Declare socket file descriptor and buffer
    int sockfd;
    char* buffer = malloc((size_t)BUF_SIZE); 

    //Declare server address to accept
    char* server_address = argv[1]; //1st argument passed in is server ip address

    //Declare host --> don't need to do
    
    //Open a socket, if successful, returns
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        printf("There was an error opening the TCP socket");
        return 1;
    }
    
    //Set the server address to send using socket addressing structure
    struct sockaddr_in serverSocket;
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_addr.s_addr = inet_addr(server_address); //convert ip address passed in into correct format
    serverSocket.sin_port = htons(atoi(argv[2])); //convert port number passed in to correct format
    
    //Connect to the server using server's ip address
    socklen_t serverAddrSize = sizeof(serverSocket); //store server address size to connect
    connect(sockfd, (struct sockaddr*)&serverSocket, serverAddrSize);
    
    //Client sends the name of the file to retrieve from the server
    buffer = argv[3]; //file name to retrieve
    int n = write(sockfd, buffer, BUF_SIZE); //send src file name
    if (n < 0) printf("ERROR writing to socket");
    
    //Client begins to write and read from the server
    //open destination file
    int dst_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);	
    if (dst_fd < 0) { // open() error checking
      printf("unable to open/create %s for writing\n", argv[4]);
      close(dst_fd);
      exit(0);
    }

    //read from server
    int n4;
    bzero(buffer, BUF_SIZE);
    while ((n4 = read(sockfd, buffer, BUF_SIZE)) > 0) //While still data being read
    {
        int nw = write(dst_fd, buffer, n4); //write to destination file
    }
        
    //Close socket descriptor
    close(sockfd);
    
    return 0;
}

