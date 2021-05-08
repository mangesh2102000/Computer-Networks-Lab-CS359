/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 3 
filename : tcp_server.c
*/

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <openssl/md5.h>

#define MAX_SIZE 1024
#define PORT 8048

int n, nBytes;
char buffer[MAX_SIZE];
char filename[105] = "temp_\0";
FILE * fp;

void calculate_md5(int sockfd) {
    // recieve file from client and calculate MD5 checksum and send it to client for verification
    unsigned char md5_checksum[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext;

    MD5_Init( & mdContext);
    while (nBytes > 0) {
        bzero(buffer, MAX_SIZE);
        n = read(sockfd, buffer, sizeof(buffer));
        MD5_Update( & mdContext, buffer, n);
        fwrite(buffer, 1, n, fp);
        nBytes -= n;
    }

    MD5_Final(md5_checksum, & mdContext);
    fclose(fp);

    write(sockfd, md5_checksum, MD5_DIGEST_LENGTH);
}

void transfer(int sockfd) {
    while (1) {
        printf("Waiting to recieve from client... \n");
        bzero(buffer, MAX_SIZE);

        // read the message from client and copy it in buffer 
        read(sockfd, buffer, sizeof(buffer));

        // if msg contains "exit" then server exits and connection is aborted. 
        if (strncmp("exit", buffer, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }

        // read the file size
        read(sockfd, & nBytes, sizeof(nBytes));

        // print the contents from client
        printf("File recieved from client: %s, filesize: %d bytes\n", buffer, nBytes);
        strcpy(filename + 5, buffer);

        // copy message from server in the buffer and send it to the client
        bzero(buffer, MAX_SIZE);
        strcpy(buffer, "Hello Client!");
        write(sockfd, buffer, sizeof(buffer));
        fp = fopen(filename, "wb");

        if (fp == NULL) {
            printf("%s can't be opened.\n", filename);
            exit(1);
        }

        calculate_md5(sockfd);
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