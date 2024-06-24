/*
* Name: Tiffany Nguyen
* Date: April 24, 2024
* Title: Lab 4 - Part 1
* Description: UDP server (peer) that receives a file from a client (peer) 
* and writes it into a destination file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

//Declare a Header structure that holds length of a packet
typedef struct {
    int len;
} Header;

//Declare a packet structure that holds data and header
typedef struct {
    Header header;
    char data[10];
} Packet;

//Declare client address to fill in address of sender
struct sockaddr_in servAddr, clienAddr;

//Printing received packet
void printPacket(Packet packet) {
    printf("Packet{ header: { len: %d }, data: \"", packet.header.len);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

//Server sending ACK to the client
void serverSend(int sockfd, const struct sockaddr *address, socklen_t addrlen) {
    Packet packet;	
    //make acknowledgement packet
    strcpy(packet.data, "Acknowled");
    packet.header.len=sizeof(packet.data); //set acknowledge packet length
	
    //send acknowledgement packet
    sendto(sockfd, (void *) &packet, sizeof(packet), 0, (struct sockaddr *) address, addrlen);
    printf("\t Server sending %s \n", packet.data);
}

Packet serverReceive(int sockfd, struct sockaddr *address, socklen_t *addrlen) {
    Packet packet;
    while (1) {
        //recv packets from the client
	    recvfrom(sockfd, (void *) &packet, sizeof(packet), 0, (struct sockaddr *) address, addrlen);
        
        // print received packet
        printPacket(packet);
        
        //send acknowldgement
	    serverSend(sockfd, address, *addrlen);
        break;
    }
    return packet;
}


int main(int argc, char *argv[]) {
    //Get from the command line, server IP and dst file
    if (argc != 3) {
        printf("Usage: %s <port> <dstfile>\n", argv[0]);
        exit(0);
    }

    //Declare socket file descriptor.
    int serverfd; 

    //Open a UDP socket, if successful, returns a descriptor
    if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("cannot create socket");
        return 0;
    }

    //Setup the server address to bind using socket addressing structure
    struct sockaddr_in serverSocket;
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(atoi(argv[1]));
    serverSocket.sin_addr.s_addr = htonl (INADDR_ANY);

    socklen_t serverAddrSize = sizeof(serverSocket);

    //bind IP address and port for server endpoint socket
    bind(serverfd, (struct sockaddr*)&serverSocket, serverAddrSize);

    //open file given by argv[2], create if it does not exist
    int fp = open(argv[2], O_CREAT | O_RDWR, 0666);
    if(fp < 0){
	    perror("File failed to open\n");
	    exit(1);
    }

    // get file contents (as packets) from client
    Packet packet;
    socklen_t addr_len = sizeof(clienAddr);
    printf("Waiting for packets to come.....\n");
    do {
        //receive packet from client
        packet = serverReceive(serverfd, (struct sockaddr*)&serverSocket, &serverAddrSize);

        //write received packet into destination file (fp)
	    write(fp, packet.data, (size_t)packet.header.len);
    } while (packet.header.len != 0); //stop when receive empty packet

    //close file and socket
    close(serverfd);
    close(fp);
    
    return 0;
}
