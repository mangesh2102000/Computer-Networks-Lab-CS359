/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 10
filename : tcp_client_1.c
*/

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_SIZE 1024
#define PORT 8048

int n, nBytes;
char buffer[MAX_SIZE];

void transfer(int sockfd) {

    while (1) {
        bzero(buffer, MAX_SIZE);
        printf("\nEnter string to send to server (\"exit\" to quit) : ");
        n = 0;
        scanf("%[^\n]%*c", buffer);

        if ((strncmp(buffer, "exit", 4)) == 0) {
            //send the exit to the server
            write(sockfd, buffer, sizeof(buffer));
            printf("client is quitting...\n");
            break;
        }

        //send the string to the server
        write(sockfd, buffer, sizeof(buffer));
        bzero(buffer, MAX_SIZE);

         // receive UPPER CASE converted string  and display it
        read(sockfd, buffer, sizeof(buffer));
        printf("Received UPPER CASE string from server: %s\n", buffer);
		bzero(buffer, MAX_SIZE);
       
    }

}

int main() {
    char * ip = "127.0.0.1";
    int e;

    int sockfd;
    struct sockaddr_in serv_addr;

    // Create and Verify socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    bzero( & serv_addr, sizeof(serv_addr));

    // assign IP, PORT 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(PORT);

    // connect the client socket to server socket 
    e = connect(sockfd, (struct sockaddr * ) & serv_addr, sizeof(serv_addr));
    if (e < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    // function for data transfer between client and server 
    transfer(sockfd);

    // close the socket 
    printf("[+]Closing the connection.\n");
    close(sockfd);

    return 0;
}