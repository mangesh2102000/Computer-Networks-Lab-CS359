/*Name : Chandrawanshi Mangesh Shivaji
Roll No. : 1801CS16
CS359 Assignment 2 
fileName : server.c
*/ 

// server code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define IP_PROTOCOL 0 
#define PORT_NO 15050 
#define NET_BUF_SIZE 200
#define cipherKey '$' 
#define sendrecvflag 0 
#define nofile "NOTFOUND" 

char fileName[NET_BUF_SIZE];
char word[NET_BUF_SIZE],word_to_send[NET_BUF_SIZE];

// function to clear buffer 
void clearBuf(char* b) 
{ 
	int i; 
	for (i = 0; i < NET_BUF_SIZE; i++) 
		b[i] = '\0'; 
} 

// function to encrypt 
char Cipher(char ch) 
{ 
	return ch ^ cipherKey; 
} 

// function sending file 
int sendFile(FILE* fp, char* buf, int s,int flag) 
{ 
	// if fp is NULL set buf to file not found and exit 
	int i, len; 
	if (fp == NULL) { 
		clearBuf(buf); 
		strcpy(buf, nofile); 
		strcpy(word_to_send,nofile);
		len = strlen(nofile); 
		for (i = 0; i < len; i++) 
			buf[i] = Cipher(buf[i]); 
		return 1;
	} 

	int requested_word=0, count=0;

	// get i from WORDi
	if(flag)
	{
		requested_word=1;
	}
	else
	{
		for(int i=4;i<strlen(buf);i++)
		{
			requested_word=requested_word*10+(buf[i]-'0');
		}
		requested_word++;
	}

	//Getting the ith word from the file (WORD means a line).
	printf("Word Requested by Client -- WORD%d\n",requested_word-1);

	clearBuf(buf);

	// READ the required line from file and store it to the buf and word_to_send

	char read_line[NET_BUF_SIZE];
	bzero(read_line,sizeof(read_line));
	bzero(word_to_send,sizeof(word_to_send));
	int idx = 0;
    while (fgets(read_line, sizeof(read_line), fp)) {
        idx++;
        if(idx == requested_word )
            strcpy(word_to_send,read_line);  
    }

	char ch, ch2; 
	for (i = 0; i < strlen(word_to_send); i++) { 
		ch = word_to_send[i];
		ch2 = Cipher(ch); 
		buf[i] = ch2; 
	} 
	
	return 1; 
} 

// driver code 
int main() 
{ 
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = INADDR_ANY; 
	char net_buf[NET_BUF_SIZE]; 
	FILE* fp; 

	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL); 

	if (sockfd < 0) 
		printf("\nfile descriptor not received!!\n"); 
	else
		printf("\nfile descriptor %d received\n", sockfd); 

	// bind() 
	if (bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con)) == 0) 
		printf("\nSuccessfully binded!\n"); 
	else
		printf("\nBinding Failed!\n"); 

	int flag=1;

	while(1)
	{ 
		if(flag == 1)
		{
			printf("\nWaiting for file name...\n"); 

			// receive file name 
			clearBuf(net_buf); 

			nBytes = recvfrom(sockfd, net_buf,NET_BUF_SIZE, sendrecvflag,(struct sockaddr*)&addr_con, &addrlen); 

			strcpy(fileName,net_buf);

			fp = fopen(fileName, "r");
			
			printf("\nFile Name Received: %s\n", net_buf); 

			if (fp == NULL) 
				printf("\nFile open failed!\n"); 
			else
				printf("\nFile Successfully opened!\n");
		}
		else
		{
			// Set fp to start for every read of word
			// This can allow us to query random wordi with some modification easily  
			fseek(fp, 0, SEEK_SET);

			// recieve next word
			clearBuf(net_buf); 
			
			nBytes = recvfrom(sockfd, net_buf,NET_BUF_SIZE, sendrecvflag,(struct sockaddr*)&addr_con, &addrlen); 
		}

		if(!flag && (net_buf[0]!='W' || net_buf[1]!='O' || net_buf[2]!='R' || net_buf[3]!='D'))
		{
			// Check format of the request by client 

			clearBuf(net_buf); 
			strcpy(net_buf, "WRONG FORMAT!!"); 
			
			int len = strlen(net_buf); 
			
			for (int i = 0; i < len; i++) 
				net_buf[i] = Cipher(net_buf[i]); 
			
			sendto(sockfd, net_buf, NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con, addrlen);

			continue;
		}
		else if(sendFile(fp, net_buf, NET_BUF_SIZE,flag) ) 
		{ 
			sendto(sockfd, net_buf, NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con, addrlen);  


			// Check which word is sent and exit if END or NOTFOUND is sent 

			if(( strncmp(word_to_send, "NOTFOUND", 8)) == 0 )
			{
				printf("\n");
				exit(1);
			}

			if( (strncmp(word_to_send, "END", 3)) == 0)
			{
				printf("\n");
				fclose(fp); 
				exit(1);
			}			
		} 
		else
		{
			fclose(fp); 
			return 0;
		}
		
		clearBuf(net_buf); 
		flag=0;
	} 
	return 0; 
}