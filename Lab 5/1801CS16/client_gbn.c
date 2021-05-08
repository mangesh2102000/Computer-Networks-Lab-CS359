/* Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801CS16
CS359 Assignment 5 
Filename: client_go_back_n.c
*/ 

#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdbool.h>
#include <math.h>
#include <errno.h>
#include <sys/stat.h>
#include <netdb.h>
#include <ctype.h>

#define MAX_SIZE 1024
#define IP_ADDRESS "127.0.0.1"
#define PORT_NO 6048 

int WINDOW_SIZE = 0;

void check_socket_creation(int sockfd)
{
	if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
}

// driver code
int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		printf("Invalid Input Format! Usage: ./client_go_back_n WINDOW_SIZE\n");
		exit(0);
	}

	WINDOW_SIZE = atoi(argv[1]);

	// Establish connection to the server
	int sockfd,nBytes;
	struct sockaddr_in addr_con;
	int addrlen = sizeof(addr_con);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	check_socket_creation(sockfd);
    printf("[+]Client socket created successfully.\n");

    addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS);

	// Declare Variables to store messages sent and received
	char buffer[MAX_SIZE];
	char seq[32];
	int seq_num = 0;

	printf("Window Size is %d, Use sequence numbers starting from 0\n", WINDOW_SIZE);

	// Go Back N Protocol 
	int flag = 0;
	while(1){

		// Take Current set of messages from the user as input and send to the server
		printf("******************************************\n");
		printf("Enter current set of messages (count = (%d)WINDOW_SIZE) to send ('exit' to quit):\n(Format for each msg : line1 = data_msg, line2 = seq_num)\n", WINDOW_SIZE);

		for(int i=0;i<WINDOW_SIZE;i++)
		{
			bzero(buffer, MAX_SIZE);
			bzero(seq, 32);

			fgets(buffer, 1024, stdin);
			buffer[strlen(buffer)-1] = '\0';
			
			// Check for exiting the program
			if(strncmp(buffer,"exit",4) == 0){
				flag = 1;
				break;
			}

			fgets(seq, 32, stdin);
			seq[strlen(seq)-1] = '\0';
			seq_num = atoi(seq);

			// Send message along with sequence number to the server
			sendto(sockfd, buffer, MAX_SIZE, 0, (struct sockaddr*)&addr_con, addrlen);
			sendto(sockfd, seq, 32, 0, (struct sockaddr*)&addr_con, addrlen);
		}

		// exit program
		if(flag == 1)
			break;	

		// Receive ACK or NAK from the server, depending on the sent message order cummulatively
		// ACK x - represents all messages from sequence number 0 to x are successfully received by the server
		// NAK x - represents that message x is not received by the server, all messages from 0 to (x-1) are successfully received
		// In the NAK scenario user may send messages from sequence number x again in order
		// In the ACK scenario user may send messages from sequence number x + 1 (hopefully in order)

		bzero(buffer, MAX_SIZE);
		recvfrom(sockfd, buffer, MAX_SIZE, 0, (struct sockaddr*)&addr_con, &addrlen);
		printf("%s\n", buffer);

		printf("******************************************\n");
	}

	printf("[+]Closing the connection.\n");
  	close(sockfd);
	return 0;
}