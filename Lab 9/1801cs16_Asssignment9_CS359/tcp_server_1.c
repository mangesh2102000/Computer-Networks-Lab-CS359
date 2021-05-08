/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 9
filename : tcp_server_1.c
*/

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SIZE 1024
#define PORT 8048

int n, nBytes;
char buffer[MAX_SIZE];

void transfer(int sockfd) {
    while (1) {

        printf("\nWaiting to recieve from client... \n");
        bzero(buffer, MAX_SIZE);

        // read the message  string from client and copy it in buffer 
        read(sockfd, buffer, sizeof(buffer));

        // if msg contains "exit" then server exits and connection is aborted. 
        if (strncmp("exit", buffer, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }

        // print the contents from client
        printf("String recieved from client: %s\n", buffer);

        // calculate number of vowels in string
        int count_of_vowels = 0;

        for(int i=0;;i++){
            
            if(buffer[i] == '\0' || buffer[i] == '\n')
                break;

            if(buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u' || buffer[i] == 'A' || buffer[i] == 'E' || buffer[i] == 'I' || buffer[i] == 'O' || buffer[i] == 'U' )
            {
                count_of_vowels++;
            }
        }

        printf("Number of vowels in recieved string is %d\n", count_of_vowels);

        // copy message from server in the buffer and send it to the client
        bzero(buffer, MAX_SIZE);

        strcpy(buffer, "String recieved successfully");
        write(sockfd, buffer, sizeof(buffer));
    }
}

// Driver function 
int main() {
    int e;

    int sockfd, new_sock;
    struct sockaddr_in serv_addr, new_addr;
    socklen_t addr_size;

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
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification 
    e = bind(sockfd, (struct sockaddr * ) & serv_addr, sizeof(serv_addr));

    if (e < 0) {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n");

    // Now server is ready to listen and verification 
    if (listen(sockfd, 10) == 0) {
        printf("[+]Listening....\n");
    } else {
        perror("[-]Error in listening");
        exit(1);
    }
    addr_size = sizeof(new_addr);

    // Accept the data packet from client and verification 
    new_sock = accept(sockfd, (struct sockaddr * ) & new_addr, & addr_size);
    if (new_sock < 0) {
        printf("Server acccept failed...\n");
        exit(0);
    } else
        printf("Server acccepted the client data packet\n");

    // Function for data transfer between client and server 
    transfer(new_sock);

    // After transfer close the socket
    printf("[+]Closing the connection.\n");
    close(sockfd);

    return 0;
}