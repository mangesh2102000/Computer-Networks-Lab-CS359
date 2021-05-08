/* Name: Chandrawanshi Mangesh Shivaji
Roll Number: 1801cs16
CS359 Lab Assignment 8
Filename: proxy.c */

/* Compilation and Execution
$ gcc proxy.c -o SimProxy
$ ./Simproxy ./SimProxy <listen_port> <institute_proxy_IP> <institute_proxy_port>
*/

// Set the browser Proxy IP to your machine IP 
// set the browser proxy to 8181(preferred) and use same in command line. 
// Detailed Report is also attaced in the zip

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <signal.h>

#define STDIN 0
#define MAX_SIZE 1024
#define N 1000		// Max connections at a time 

// driver code
int main(int argc, char const *argv[])
{
	// SIGPIPE is the "broken pipe" signal, which is sent to a process when it attempts to write to a pipe whose read
	// end has closed (or when it attempts to write to a socket that is no longer open for reading), but not vice versa. 
	// The default action is to terminate the process.

	// ignore SIGPIPE
	signal(SIGPIPE, SIG_IGN);

	// Validation of Input
	if(argc != 4){
        printf("Error: Invalid command line arguments\n");
        printf("Usage:\t./SimProxy <listen port> <institute_proxy_IP> <institute_proxy_port>\n");
        return 0;
	}

	struct sockaddr_in institue_address, browser_address, client_address;
	socklen_t len, len_client;

	bzero(&browser_address, sizeof(browser_address));
	bzero(&institue_address, sizeof(institue_address));

	// Create Socket
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(!sockfd){
		printf("Socket creation failed\n");
		exit(1);
	}

	// Make socket non-blocking through the fcntl() system call
	int check = fcntl(sockfd, F_SETFL, O_NONBLOCK);	
	if(check == -1){
		printf("Unable to make socket non-blocking\n");
		exit(2);
	}

	int set = 1;
	// Set options for socket
	int sso = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));
	if(sso!=0){
		printf("Unable to set options for socket\n");
		exit(3);
	}

	browser_address.sin_family = AF_INET;
	browser_address.sin_addr.s_addr = htonl(INADDR_ANY);
	browser_address.sin_port = htons(atoi(argv[1]));

	institue_address.sin_family = AF_INET;
	institue_address.sin_port = htons(atoi(argv[3]));

	// Convert IP address from text to binary
	int ipton = inet_pton(AF_INET, argv[2], &institue_address.sin_addr);
	if(ipton != 1){
		printf("Proxy Server Address Invalid, Please check input again.\n");
		exit(4);
	}

	// Bind
	int e = bind(sockfd, (struct sockaddr*)&browser_address, sizeof(browser_address));
	if(e!=0){
		printf("Socket could not be bound\n");
		exit(5);
	}

	// Listen to connections
	if(listen(sockfd, N) < 0){
		printf("Listen Failure\n");
		exit(6);
	}

	// Variables to store file descriptors
	int nFD, nselect;
	fd_set get_set, send_set;
	int fd_get[N], fd_send[N];

    char buffer[MAX_SIZE];
    bzero(&buffer, sizeof(buffer));
	
	// Initialize to zero
	FD_ZERO(&get_set);
	FD_ZERO(&send_set);

	// Initialize timeout vale
	struct timeval timeout;
    timeout.tv_sec  = 0;
    timeout.tv_usec = 1;

	printf("Proxy currently running on PORT %s\n", argv[1]);
    printf("All connections are forwared to %s:%s\n", argv[2], argv[3]);

    int cnt = 0;
    while(1){

    	// Accept New incoming connections (if not reached max limit = N)
    	if(cnt < N){
    		
    		fd_get[cnt] = accept(sockfd, (struct sockaddr *)&client_address, &len_client);
    		if(fd_get[cnt] >= 0){

    			// create new socket for outgoing connection
    			fd_send[cnt] = socket(AF_INET, SOCK_STREAM, 0);
    			if(fd_send[cnt] == -1){
    				printf("Socket Creation Failed\n");
    				exit(1);
    			}

    			// Convert IP address back to text and store it
    			char ip_str[105];
    			inet_ntop(AF_INET, &(client_address.sin_addr), ip_str, 105);

    			int ip_port = (int)(ntohs(client_address.sin_port));
    			printf("Connection accepted from %s:%d\n", ip_str, ip_port);

    			// Make socket non-blocking through the fcntl() system call
				check = fcntl(fd_send[cnt], F_SETFL, O_NONBLOCK);	
				if(check == -1){
					printf("Unable to make socket non-blocking\n");
					exit(2);
				}

				// connect socket to institute address
				connect(fd_send[cnt], (struct sockaddr *)&institue_address, sizeof(institue_address));
				cnt += 1;
    		}
    	}

    	// Initialize to zero
		FD_ZERO(&get_set);
		FD_ZERO(&send_set);
		FD_SET(0, &get_set);

		// Stores highest numbered file descriptor in any of sets + 1
		nFD = 1;

		// Add all connections to FD SET
		for(int i=0;i<cnt;i++){
			FD_SET(fd_get[i], &get_set);
			FD_SET(fd_get[i], &send_set);
			FD_SET(fd_send[i], &get_set);
			FD_SET(fd_send[i], &send_set);
			if(fd_get[i] > nFD)
				nFD = fd_get[i];
			if(fd_send[i] > nFD)
				nFD = fd_send[i];
		}
		nFD += 1;

		// nselect stores the number of file descriptors contained in the three returned descriptor sets 
		// (that is, the total number of bits that are set in readfds, writefds, exceptfds) 
		nselect = select(nFD, &get_set, &send_set, NULL, &timeout);
			
		// at least one file descriptor is ready
		if(nselect > 0){

			if(FD_ISSET(0, &get_set)!=0){				

				// if user enters "exit", close program (along with all connections)
    			bzero(&buffer, sizeof(buffer));
				read(STDIN, buffer, sizeof(buffer));
				len = strlen(buffer);
				buffer[len-1] = 0;

				if( strncmp(buffer, "exit", 4) == 0 ){
					int num = sysconf(_SC_OPEN_MAX);
					for(int i=3;i<num;i++)
						close(i);
					return 0;
				}
			}

			for(int i=0;i<cnt;i++){

				int bytesRead, bytesSent;
				
				if( FD_ISSET(fd_get[i], &get_set)!=0 && FD_ISSET(fd_send[i], &send_set) != 0){
					bzero(&buffer, sizeof(buffer));
					bytesRead = read(fd_get[i], buffer, sizeof(buffer));
					bytesSent = send(fd_send[i], buffer, bytesRead, 0);
				}

				if( FD_ISSET(fd_send[i], &get_set)!=0 && FD_ISSET(fd_get[i], &send_set) != 0){
					bzero(&buffer, sizeof(buffer));
					bytesRead = read(fd_send[i], buffer, sizeof(buffer));
					bytesSent = send(fd_get[i], buffer, bytesRead, 0);
				}
			}
		}
    }

	return 0;
}