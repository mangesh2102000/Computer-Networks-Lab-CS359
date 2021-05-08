/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 7
filename : receiver.c
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

int pow2[8];

void check_socket_creation(int sockfd){
	if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
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

// Function to check validity of CRC code for current 4 bits
int check_recv_crc(int recv_crc[], int recv_ascii_char[])
{
	int crc_divisor[4] = {1,0,1,1};
	int remainder[3];
	int check_error = 0;

	mod2div(recv_crc, crc_divisor, remainder);

	for(int i=0;i<3;i++){
		if(remainder[i] != 0){
			check_error = 1;
			break;
		}
	}

	if(check_error == 0) 
	{
		recv_ascii_char[0] = recv_crc[0];
		recv_ascii_char[1] = recv_crc[1];
		recv_ascii_char[2] = recv_crc[2];
		recv_ascii_char[3] = recv_crc[3];
		printf("[+]Remainder is zero. No error while transmission of data\t");
		return(1);
	}
	else 
	{
		printf("[-]Error Detected!, Remainder is non-zero.\n");
		return(0);
	}
}

// Function to convert given ascii bits to char
char convert_ascii_to_char(int recv_ascii_char[]){
	int num = 0;
	for(int i=0;i<8;i++){
		if(recv_ascii_char[i] == 1){
			num += pow2[i];
		}
	}
	char c = (char)num;
	return c;
}

// Function to receive CRC code from sender and convert it to corresponding charater
void recv_data(int sockfd){

	int nBytes;
	char c ='a';
	int recv_crc[7];
	int recv_ascii_char[8]={0};

	while(1){
		
		nBytes = recv(sockfd, recv_crc, 7*8, sendrecvflag);
	
		if(nBytes > 0){

			if( check_recv_crc(recv_crc, &recv_ascii_char[0]) ){
				send(sockfd, "ACK", sizeof("ACK"), 0);
			}else{
				send(sockfd, "NAK", sizeof("NAK"), 0);
			}
			
			printf(" CRC Code for first 4 bits : ");
			for(int i=0;i<7;i++){
				printf("%d", recv_crc[i]);
			}
			printf("\n");

			bzero(recv_crc, 7);

			nBytes = recv(sockfd, recv_crc, 7*8, sendrecvflag);

			if(nBytes > 0){
				
				if( check_recv_crc(recv_crc, &recv_ascii_char[4]) ){
					send(sockfd, "ACK", sizeof("ACK"), 0);
				}else{
					send(sockfd, "NAK", sizeof("NAK"), 0);
				}

				printf(" CRC Code for last 4 bits : ");
				for(int i=0;i<7;i++){
					printf("%d", recv_crc[i]);
				}
				printf("\n");

				bzero(recv_crc, 7);

				c = convert_ascii_to_char(recv_ascii_char);
				printf(" Received Character : %c\n\n", c);
			}
			else{
				break;
			}
		}
		else{
			break;
		}

		bzero(recv_crc, 7);
		bzero(recv_ascii_char, 8);
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
    printf("[+]Receiver side socket created successfully.\n");

	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT); 
	addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS); 

	int e = bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con));
	if (e < 0) {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n"); 

    if(listen(sockfd, 5) == 0){
    	printf("[+]Listening...\n");
    }
    else{
    	printf("[-]Error in Listening\n");
    	exit(1);
    }

    pow2[0] = 1;
    for(int i=1;i<8;i++){
    	pow2[i] = pow2[i-1] * 2;
    }

   	int new_sock;
   	struct sockaddr_in new_addr;
   	socklen_t addr_size;

   	addr_size = sizeof(new_addr);
  	new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

   	recv_data(new_sock);
   	printf("[+]Data received successfully.\n");

   	return 0;
}


