/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 6 
filename : sender.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/md5.h>

#define PORT 6032
#define IP_ADDRESS "127.0.0.1"
#define sendrecvflag 0 
#define IP_PROTOCOL 0

void check_socket_creation(int sockfd){
	if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
}

void convert_char_to_ascii(int ascii_char[], char c){
	int num = (int)c;
	int i=0;
	while(i < 8){
		ascii_char[i] = num % 2;
		num /= 2;
		i++;
	}
}

void convert_to_hamming_code(int hamming_code[], int ascii_char[]){
	
	hamming_code[0] = ascii_char[0];
	hamming_code[1] = ascii_char[1];
	hamming_code[2] = ascii_char[2];
	hamming_code[4] = ascii_char[3];

	hamming_code[6] = hamming_code[0]^hamming_code[2]^hamming_code[4];
	hamming_code[5] = hamming_code[0]^hamming_code[1]^hamming_code[4];
	hamming_code[3] = hamming_code[0]^hamming_code[1]^hamming_code[2];

	for(int i=0;i<7;i++){
		printf("%d", hamming_code[i]);
	}
}

void send_data(FILE* fp, int sockfd){

	char c;
	int ascii_char[8]={0,0,0,0,0,0,0,0};
	int hamming_code[7];

	while(1){
		c = fgetc(fp);
		if(c == EOF) 
			break;

		printf(" Sent Character : %c\n", c);

		convert_char_to_ascii(ascii_char, c);
		
		printf(" Hamming Code for first 4 bits : ");
		convert_to_hamming_code(hamming_code, &ascii_char[0]);
		printf("\n");
		if (send(sockfd, hamming_code, sizeof(hamming_code), 0) == -1) 
	    {
	        perror("[-]Error in sending data.");
	        exit(1);
	    }
		bzero(hamming_code, 7);
		usleep(1000);

		printf(" Hamming Code for last 4 bits : ");
		convert_to_hamming_code(hamming_code, &ascii_char[4]);
		printf("\n\n");
		if (send(sockfd, hamming_code, sizeof(hamming_code), 0) == -1) 
	    {
	        perror("[-]Error in sending data.");
	        exit(1);
	    }
		bzero(hamming_code, 7);
		bzero(ascii_char, 8);
		usleep(1000);
	}
}

int main(int argc, char const *argv[]) 
{ 
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con);

	sockfd = socket(AF_INET, SOCK_STREAM, IP_PROTOCOL); 

	check_socket_creation(sockfd);
    printf("[+]Sender side socket created successfully.\n");

	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT); 
	addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS); 

	int e = connect(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con));
	if (e < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Reciever\n"); 

    FILE* fp;
    fp = fopen("send.txt", "r");

    if (fp == NULL) {
    	printf("[-]Error in reading file. Check File : send.txt exists or not\n");
    	exit(1);
   	}

   	send_data(fp, sockfd);
   	printf("[+]Data sent successfully.\n");
   	fclose(fp);

 	printf("[+]Closing the connection.\n");
  	close(sockfd);

   	return 0;
}


