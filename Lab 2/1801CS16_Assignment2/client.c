/*Name : Chandrawanshi Mangesh Shivaji
Roll No. : 1801CS16
CS359 Assignment 2 
fileName : client.c
*/ 

// client code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define IP_PROTOCOL 0 
#define IP_ADDRESS "127.0.0.1" // localhost 
#define PORT_NO 15050 
#define NET_BUF_SIZE 200 
#define cipherKey '$' 
#define sendrecvflag 0 


FILE *fp;
char fileName[NET_BUF_SIZE];


// function to clear buffer 
void clearBuf(char* b) 
{ 
	int i; 
	for (i = 0; i < NET_BUF_SIZE; i++) 
		b[i] = '\0'; 
} 

// function for decryption 
char Cipher(char ch) 
{ 
	return ch ^ cipherKey; 
} 

// function to receive each word from file 
int recvFile(char* buf, int s) 
{ 
	// Store the received word from server and print it to client side 
	int i; 
	char ch;
	char word[NET_BUF_SIZE]; 
	clearBuf(word);
	for (i = 0; i < strlen(buf); i++) { 
		ch = buf[i]; 
		ch = Cipher(ch); 
		word[i]=ch;
		printf("%c", ch); 
	} 

	// Check the response from server and act accordingly 
	if((strncmp(word, "NOTFOUND", 8)) == 0)
	{
		printf("\n-------------------------------\n"); 
		exit(1);
	}
	
	// A local file named "client_file.txt" is created and opened in write mode on recieving HELLO
	if( (strncmp(word, "HELLO", 5)) == 0 ) 	
	{	
		fp = fopen("client_file.txt", "w");
		// fputs(word,fp);	 // if you want to write HELLO to file remove this comment
	}
	else if( (strncmp(word, "END", 3)) == 0)   //On recieving the word END the file is closed and the client exits
	{
		// fputs(word,fp);	 // if you want to write END to file remove this comment
		fclose(fp);
		printf("\n-------------------------------\n"); 
		exit(1);
	}
	else
	{
		// Each Word after HELLO till END is wriiten onto the file created
		fputs(word,fp);			
	}

	return 1; 
} 

// driver code 
int main(int argc,char *argv[]) 
{ 
	strcpy(fileName,argv[0]);
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
	char net_buf[NET_BUF_SIZE]; 

	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL); 

	if (sockfd < 0) 
		printf("\nfile descriptor not received!!\n"); 
	else
		printf("\nfile descriptor %d received\n", sockfd);

	//Flag to check if fileName is already povided or not
	int flag=1; 	
	int word_idx=1;		//current word number
	int data_recv=0;	//flag to check data is being received ot not
	while (1) 
	{ 
		if(flag)
		{
			printf("\nPlease enter file name to receive:\n"); 
			scanf("%s", net_buf); 

			// send fileName to server 
			sendto(sockfd, net_buf, NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen); 
			
			// set to zero as fileName is recieved
			flag=0;
		}
		else
		{
			// Calculate current WORDi to be requested from the server
			char word[]="WORD";
			char number[10];
			clearBuf(number);
			sprintf(number, "%d", word_idx);
			word_idx++;
			strcat(word,number);
			strcpy(net_buf,word);

			//Sending the WORDi to the server
			sendto(sockfd, net_buf, NET_BUF_SIZE,sendrecvflag, (struct sockaddr*)&addr_con,addrlen); 
		}

		if(data_recv == 0)
		{
			data_recv=1;
			printf("\n---------Data Received---------\n"); 
		}

		// receive the word from server 
		clearBuf(net_buf); 

		nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE,sendrecvflag, (struct sockaddr*)&addr_con,&addrlen); 

		// Write the recived word to a file as told in assignment 
		// I have not written HELLO and END to this file, though it is possible with minor edits 
		recvFile(net_buf, NET_BUF_SIZE); 
	} 

	printf("\n-------------------------------\n"); 
	return 0; 
} 