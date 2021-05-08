/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 6 
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

int check_recv_hamming_code(int recv_hamming_code[], int recv_ascii_char[])
{
	int c,c1,c2,c3;

	c1=recv_hamming_code[6]^recv_hamming_code[4]^recv_hamming_code[2]^recv_hamming_code[0];
	c2=recv_hamming_code[5]^recv_hamming_code[4]^recv_hamming_code[1]^recv_hamming_code[0];
	c3=recv_hamming_code[3]^recv_hamming_code[2]^recv_hamming_code[1]^recv_hamming_code[0];
	c=c3*4+c2*2+c1 ;
  
	if(c==0) 
	{
		recv_ascii_char[0] = recv_hamming_code[0];
		recv_ascii_char[1] = recv_hamming_code[1];
		recv_ascii_char[2] = recv_hamming_code[2];
		recv_ascii_char[3] = recv_hamming_code[4];
		printf("[+]No error while transmission of data\t");
		return(1);
	}
	else 
	{
		printf("[-]Error on position %d",c);
        
		printf("\tData received : ");

	    for(int i=0;i<7;i++)
	      printf("%d",recv_hamming_code[i]);
		
		printf("\tCorrected message is : ");
 
		if(recv_hamming_code[7-c]==0){
			recv_hamming_code[7-c]=1;
		}
        else{
			recv_hamming_code[7-c]=0;
        }
		
		recv_ascii_char[0] = recv_hamming_code[0];
		recv_ascii_char[1] = recv_hamming_code[1];
		recv_ascii_char[2] = recv_hamming_code[2];
		recv_ascii_char[3] = recv_hamming_code[4];
		return(0);
	}
}

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

void recv_data(int sockfd){

	int nBytes;
	char c ='a';
	int recv_hamming_code[7];
	int recv_ascii_char[8]={0};

	while(1){
		
		nBytes = recv(sockfd, recv_hamming_code, 7*8, sendrecvflag);
	
		if(nBytes > 0){

			check_recv_hamming_code(recv_hamming_code, &recv_ascii_char[0]);
			printf(" Hamming Code for first 4 bits : ");
			for(int i=0;i<7;i++){
				printf("%d", recv_hamming_code[i]);
			}
			printf("\n");

			bzero(recv_hamming_code, 7);
			usleep(1000);

			nBytes = recv(sockfd, recv_hamming_code, 7*8, sendrecvflag);

			if(nBytes > 0){
				check_recv_hamming_code(recv_hamming_code, &recv_ascii_char[4]);
				printf(" Hamming Code for last 4 bits : ");
				for(int i=0;i<7;i++){
					printf("%d", recv_hamming_code[i]);
				}
				printf("\n");

				bzero(recv_hamming_code, 7);
				usleep(1000);

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

		bzero(recv_hamming_code, 7);
		bzero(recv_ascii_char, 8);
	}
}

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


