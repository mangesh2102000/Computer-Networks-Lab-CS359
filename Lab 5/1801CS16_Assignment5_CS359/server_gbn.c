/* Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801CS16
CS359 Assignment 5 
Filename: server_go_back_n.c
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
		printf("Invalid Input Format! Usage: ./server_gbn WINDOW_SIZE\n");
		exit(0);
	}

	WINDOW_SIZE = atoi(argv[1]);

	// Establish Connection with the client
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 

	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	check_socket_creation(sockfd);
	printf("[+]Server socket created successfully\n"); 

	int e = bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con));
	if (e < 0) {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n");

    // Declare Variables to store messages sent and received, verify sequence numbers, etc
	char buffer[MAX_SIZE];
	char seq[32];
	int seq_num = 0;
	int expected_seqnum = 0;

	int flag = 0;
	//  Go Back N Protocol 
	while(1)
	{
		flag = 0;

		// Receive messages along with sequence numbers from client
		for(int i=0;i<WINDOW_SIZE;i++){

			bzero(buffer, MAX_SIZE);
			bzero(seq, 32);
		
			recvfrom(sockfd, buffer, MAX_SIZE, 0, (struct sockaddr*)&addr_con, &addrlen);
			recvfrom(sockfd, seq, 32, 0, (struct sockaddr*)&addr_con, &addrlen);

			seq_num = atoi(seq);

			// If message sequence number is not expected, discard the message
			// else display the message along with sequence number
			if( seq_num != expected_seqnum ){
				flag = 1;
				printf("Message Discarded, (Sequence Number Out of Order) : Expected = %d, Found = %d\n", expected_seqnum, seq_num);
			}else{
				printf("Received Message from Client : %s\nSequence Number: %s\n", buffer, seq);
				expected_seqnum = (expected_seqnum + 1);
			}
		}

		// In case of inorder receipt of messages, send ack with last received sequence number
		if(flag == 0){
			bzero(buffer, MAX_SIZE);
			strcpy(buffer, "ACK ");
			strcat(buffer, seq);

			sendto(sockfd, buffer, MAX_SIZE, 0, (struct sockaddr*)&addr_con, addrlen);
		
		}// In case of out of order receipt of messages, send nak with expected sequence number
 		else{
			bzero(buffer, MAX_SIZE);
			strcpy(buffer, "NAK ");

			bzero(seq, 32);
			sprintf(seq, "%d", expected_seqnum);

			strcat(buffer, seq);

			sendto(sockfd, buffer, MAX_SIZE, 0, (struct sockaddr*)&addr_con, addrlen);
		}
	}

	close(sockfd);
	printf("\n-------------------------------\n"); 

	return 0;
}
