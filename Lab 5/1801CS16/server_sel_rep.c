/* Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801CS16
CS359 Assignment 5 
Filename: server_sel_rep.c
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

	// Establish connection with the client 
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

    // // Declare Variables to store messages sent and received, verify sequence numbers, etc
	char buffer[MAX_SIZE];
	char seq[32];
	int seq_num = 0;
	int expected_seqnum = 0;
	char msg_buffer[WINDOW_SIZE][MAX_SIZE];
	int seqnum_to_ack[WINDOW_SIZE];
	int curr_window_seqnum[WINDOW_SIZE];

	for(int i=0;i<WINDOW_SIZE;i++)
	{
		bzero(msg_buffer[i], MAX_SIZE);
	}

	int used_buffer_space = 0;
	int flag = 0;
	int yet_to_print = 0;
	// Selective Repeat Protocol
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

			curr_window_seqnum[i] = seq_num;

			// If message sequence number is not expected (out of order) and buffer is not full, buffer the messageand store sequence number
			// else display the message along with sequence number, along with all previouly buffered messages and sequence numbers if present
			if( seq_num != expected_seqnum ){
				yet_to_print = 1;
				flag = 1;

				if(used_buffer_space == WINDOW_SIZE){
					printf("Buffer Full\n");
					printf("Message Discarded,  (Sequence Number Out of Order) : Expected = %d, Found = %d\n", expected_seqnum, seq_num);
				}
				else{	
					seqnum_to_ack[used_buffer_space] = seq_num;
					strncpy(msg_buffer[used_buffer_space], buffer, MAX_SIZE);
					used_buffer_space++;
					printf("Message Buffered, (Sequence Number Out of Order) : Expected = %d, Found = %d\n", expected_seqnum, seq_num);
				}

			}else{

				printf("Received Message from Client : %s\nSequence Number: %s\n", buffer, seq);
				expected_seqnum = (expected_seqnum + 1);
			
				if(yet_to_print == 1)
				{
					for(int i=0;i<used_buffer_space;i++)
					{
						printf("Received Message from Client : %s\nSequence Number: %d\n", msg_buffer[i], seqnum_to_ack[i]);
						bzero(msg_buffer[i], MAX_SIZE);
						expected_seqnum++;
					}	
					yet_to_print = 0;
					used_buffer_space = 0;
				}
			}
		}

		// In case of inorder receipt of messages, send individual ACK along with sequence number
		if(flag == 0){

			for(int i=0;i<WINDOW_SIZE;i++)
			{
				bzero(buffer, MAX_SIZE);
				bzero(seq, 32);
				strcpy(buffer, "ACK ");
				sprintf(seq, "%d", curr_window_seqnum[i]);
				strcat(buffer, seq);
				sendto(sockfd, buffer, MAX_SIZE, 0, (struct sockaddr*)&addr_con, addrlen);
			}

		}// In case of out of order receipt send ACK for all printed and buffered messages, send NAK for expected sequence number
		else{

			for(int i=0;i<WINDOW_SIZE-used_buffer_space;i++)
			{
				bzero(buffer, MAX_SIZE);
				bzero(seq, 32);
				strcpy(buffer, "ACK ");
				sprintf(seq, "%d", curr_window_seqnum[i]);
				strcat(buffer, seq);
				sendto(sockfd, buffer, MAX_SIZE, 0, (struct sockaddr*)&addr_con, addrlen);
			}

			bzero(buffer, MAX_SIZE);
			strcpy(buffer, "NAK ");

			bzero(seq, 32);
			sprintf(seq, "%d", expected_seqnum);
			strcat(buffer, seq);
			sendto(sockfd, buffer, MAX_SIZE, 0, (struct sockaddr*)&addr_con, addrlen);
		
			for(int i=0;i<used_buffer_space;i++)
			{
				bzero(buffer, MAX_SIZE);
				bzero(seq, 32);
				strcpy(buffer, "ACK ");
				sprintf(seq, "%d", seqnum_to_ack[i]);
				strcat(buffer, seq);
				sendto(sockfd, buffer, MAX_SIZE, 0, (struct sockaddr*)&addr_con, addrlen);
			}
		}

	}

	close(sockfd);
	printf("\n-------------------------------\n"); 

	return 0;
}
