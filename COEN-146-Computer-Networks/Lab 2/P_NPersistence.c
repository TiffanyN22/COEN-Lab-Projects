//Name: Tiffany Nguyen
//Date: April 10, 2024
//Title: Lab 2 - Circuit Switching and Packet Switching (Step 4)
//Description: The purpose of this lab is to calculate how long it takes a client to get
//a requested object using both persistent and non-persistent HTTP
//Run: compile, when running pass in the number of parallel connections as a parameter

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {  // check correct usage
		fprintf(stderr, "usage: %s <n connections> \n", argv[0]);
		exit(1);
	}
        
	//Declare and values to n (n connections), np (np parralel connections), RTT0, RTT1, RTT2, RTTHTTP, RTTDNS, ..
	int n = 1; 
	int np = atoi(argv[1]); //read num of parallel connections from input
	int RTT0 = 3; //msec, given time for DNS server 1
	int RTT1 = 20; 
	int RTT2 = 26;
	int RTTHTTP = 47;
	int RTTDNS = RTT0 + RTT1 + RTT2; //total time for DNS lookup to find server
	int objects = 6 + 1; //1 base + 6 additional objects

	//multiply RTT by 2 because non-persistent HTTP (connect then request), RTTDNS is time to find server
	int one_obj = RTTDNS + ( 2 * RTTHTTP); 
	printf("One object: %d msec\n", one_obj);
	
	//PART B - 6 OBJECTS
	int six_obj = RTTDNS; //find DNS server
	//2 RTTs per object (to establish connection and request object), n objects
	for(int i = 0; i < objects; i++){
		six_obj+=(2*RTTHTTP);
	}
    printf("Non-Persistent 6 objects: %d msec\n", six_obj);

	//PART C - PARALLEL CONNECTIONS
	//persistent with parallel connetion 
	int p_parallel = RTTDNS + RTTHTTP; //time for initial connection, persistent so don't multiply by 2
	for(int i = 0; i < objects/np + (objects % np != 0); i++){ //how many times ran = objects/connections at once, ceiling divide
		p_parallel += RTTHTTP; //time to send/request message over open connection, don't need to reconnect
	}
	printf("%d parallel connection - Persistent: %d msec\n", np, p_parallel);

	// non-persistent with parallel connetion
	int np_parallel = RTTDNS + ( 2 * RTTHTTP); //time for initial connection
	for(int i = 0; i < objects/np + (objects % np != 0); i++){ //how many times ran = objects/connections at once, ceiling divide
		np_parallel += RTTHTTP; //send messages over open connection
	}
    printf("%d parallel connection - Non-Persistent: %d msec\n", np, np_parallel);

	return 0;
}
