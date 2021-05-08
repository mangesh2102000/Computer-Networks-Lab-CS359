/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 7
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

// Function to convert given ascii bits to char
void convert_char_to_ascii(int ascii_char[], char c){
	int num = (int)c;
	int i=0;
	while(i < 8){
		ascii_char[i] = num % 2;
		num /= 2;
		i++;
	}
}

// Function to calculate XOR of a and b arrays
void XOR(int a[], int b[], int c[]){
	for(int i=1;i<4;i++){
		c[i-1] = a[i]^b[i];
	}
}

// Function to copy array b to array a till length len
void copy_array(int a[],int b[],int len){
	for(int i=0;i<len;i++)
		a[i]=b[i];
}

// Function to perform mod-2-division
void mod2div(int crc[], int crc_divisor[], int remainder[]){

	int zeros[4] = {0,0,0,0};
	int idx = 0;
	int tmp[4];
	copy_array(tmp,crc,4);
	while(1){

		if(tmp[0] == 1)
			XOR(tmp, crc_divisor, remainder);
		else
			XOR(tmp, zeros, remainder);

		if(idx+4 >= 7)
			break;

		copy_array(tmp, remainder, 3);
		tmp[3] = crc[idx+4];
		idx++;
	}
}

// Function to generate a CRC code for current 4 bits
void convert_to_crc(int crc[], int ascii_char[]){
	
	crc[0] = ascii_char[0];
	crc[1] = ascii_char[1];
	crc[2] = ascii_char[2];
	crc[3] = ascii_char[3];
	crc[4] = crc[5] = crc[6] = 0;

	int crc_divisor[4] = {1,0,1,1};
	int remainder[3] = {0,0,0};

	mod2div(crc, crc_divisor, remainder);

	crc[4] = remainder[0];
	crc[5] = remainder[1];
	crc[6] = remainder[2];

	for(int i=0;i<7;i++){
		printf("%d", crc[i]);
	}
}

// Function to read each char from File and send it to the receiver
void send_data(FILE* fp, int sockfd){
	char c;
	int ascii_char[8]={0,0,0,0,0,0,0,0};
	int crc[7];
	char ACK[4];
	int nBytes;

	while(1){
		c = fgetc(fp);
		if(c == EOF) 
			break;

		printf(" Sent Character : %c\n", c);

		convert_char_to_ascii(ascii_char, c);
		
		printf(" CRC Code for first 4 bits : ");
		convert_to_crc(crc, &ascii_char[0]);
		printf("\t");
		if (send(sockfd, crc, sizeof(crc), 0) == -1) 
	    {
	        perror("[-]Error in sending data.");
	        exit(1);
	    }

	    nBytes = recv(sockfd, ACK, sizeof(ACK), 0);

	    if(strncmp(ACK, "ACK", 3) == 0){
	    	printf("[+]Received Positive Acknowledgement\n");
	    }
	    else{
	    	printf("[+]Received Negative Acknowledgement\n");
	    }

		bzero(crc, 7);

		printf(" CRC Code for last 4 bits : ");
		convert_to_crc(crc, &ascii_char[4]);
		printf("\t");
		if (send(sockfd, crc, sizeof(crc), 0) == -1) 
	    {
	        perror("[-]Error in sending data.");
	        exit(1);
	    }

	    nBytes = recv(sockfd, ACK, sizeof(ACK), 0);

	    if(strncmp(ACK, "ACK", 3) == 0){
	    	printf("[+]Received Positive Acknowledgement\n");
	    }
	    else{
	    	printf("[+]Received Negative Acknowledgement\n");
	    }

	    printf("\n");
		bzero(crc, 7);
		bzero(ascii_char, 8);
	}
}

// driver code
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


