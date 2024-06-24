/*
* Name: Tiffany Nguyen
* Date: April 17, 2024
* Title: Lab 3 - Part 3
* Description: Concurrent TCP server can that accept and respond to multiple
* client connections using multithreading, each connection requests a file transfer
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/mman.h> // mmap()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <stdint.h>

//Define the number of clients/threads that can be served
#define N 100
int threadCount = 0;
pthread_t clients[N]; //declaring N threads

//Declare socket and connection file descriptors.
struct sockaddr_in clientAddr;
int sockfd = 0;

//Declare receiving and sending buffers of size 10 bytes
#define BUFFER_SIZE 10

//Declare server address to which to bind for receiving messages and client address to fill in sending address
char* serverAddress;

//Connection handler (thread function) for servicing client requests for file transfer
void* connectionHandler(void* sock){
   int sockfd2 = *(int*)sock; //convert passed in socket file descriptor to int

   //declare buffer holding the name of the file from client
   char* nameBuffer = malloc((size_t)BUFFER_SIZE);
   
   //Connection established, server begins to read and write to the connecting client
   printf("Connection Established with client IP: %s and Port: %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
   
	//receive name of the file from the client, store in nameBuffer
   bzero(nameBuffer, BUFFER_SIZE);
   int n = read(sockfd2, nameBuffer, BUFFER_SIZE);
   if (n < 0) printf("ERROR reading from socket\n");
	
   //open file and send to client
   int src_fd = open(nameBuffer, O_RDONLY);	// opens a file for reading
	if (src_fd < 0) { // open() error checking
		printf("unable to open %s for reading\n", nameBuffer);
		close(src_fd);
		exit(0);
	}
     
   //read file and send to connection descriptor
   char* buf = malloc((size_t)BUFFER_SIZE);  
	int nr = 0;
	do{
		// reads up to BUF_SIZE bytes from src_fd
		nr = read(src_fd, buf, BUFFER_SIZE);
		// writes buf (bytes read) to client
		if(nr != 0){
			write(sockfd2, buf, BUFFER_SIZE);
		}
	} while(nr != 0 && nr != -1); //while data in src_fd
   
   printf("File transfer complete\n");
   
   //close file
   close(src_fd);
    
   //Close connection descriptor
   close(sockfd2);
   pthread_exit(0);
}


int main(int argc, char *argv[]){
 //Get from the command line, server IP, src and dst files.
 if (argc != 2){
	printf ("Usage: %s <port #> \n",argv[0]);
	exit(0);
 } 

 //Open a TCP socket, if successful, returns a descriptor
 sockfd = socket(AF_INET, SOCK_STREAM, 0); //parameters: domain, type, protocol
   if(sockfd<0){
      printf("There was an error opening the TCP socket");
   }

 //Setup the server address to bind using socket addressing structure
 struct sockaddr_in serverSocket;
   serverSocket.sin_family = AF_INET;
   serverSocket.sin_port = htons(atoi(argv[1])); //get passed in port number (must be >1000)
   serverSocket.sin_addr.s_addr = htonl (INADDR_ANY);

 //bind IP address and port for server endpoint socket
 socklen_t serverAddrSize = sizeof(serverSocket);
   if(bind(sockfd, (struct sockaddr*)&serverSocket, serverAddrSize)){
      printf("Socket bind failed\n");
      return 0;
   }

 // Server listening to the socket endpoint, and can queue 5 client requests
 printf("Server listening/waiting for client at port %s\n", argv[1]);
 if (listen(sockfd, 1)< 0){ //backlog = 1
   printf("listen failed\n");
}

socklen_t clientAddrSize = sizeof(clientAddr);
int new_socket; //array to hold all socket file descriptors
while (1){
   //Server accepts the connection and call the connection handler
   new_socket= accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrSize);
   
   if(pthread_create(&clients[threadCount], NULL, connectionHandler, (void*) &new_socket) < 0){
      perror("Unable to create a thread");
      exit(0);
   }
   else {
      printf("Thread %d has been created to service client request\n",++threadCount);
   }      
 }
 for(int i = 0; i < threadCount; i++){
      pthread_join(clients[i], NULL);
 }
 return 0;
}