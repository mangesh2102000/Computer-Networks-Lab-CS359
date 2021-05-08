/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 3 
filename : tcp_client.c
*/

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <openssl/md5.h>

#define MAX_SIZE 1024
#define PORT 8048

int n, nBytes;
char buffer[MAX_SIZE];
char fileName[105] = "temp_\0";
FILE * fp;

void calculate_md5_and_check(int sockfd) {
    // calculate MD5 checksum for original file
    unsigned char md5_checksum[MD5_DIGEST_LENGTH], md5_checksum_recv[MD5_DIGEST_LENGTH];;
    MD5_CTX mdContext;

    MD5_Init( & mdContext);
    nBytes = fread(buffer, 1, sizeof(buffer), fp);
    while (nBytes > 0) {
        write(sockfd, buffer, nBytes);
        MD5_Update( & mdContext, buffer, nBytes);
        bzero(buffer, MAX_SIZE);
        nBytes = fread(buffer, 1, sizeof(buffer), fp);
    }
    fclose(fp);
    MD5_Final(md5_checksum, & mdContext);

    printf("MD5 for Original File : ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        printf("%02x", md5_checksum[i]);
    printf("\n");

    // getback the value of md5 checksum from server
    bzero(md5_checksum_recv, sizeof(md5_checksum_recv));
    read(sockfd, md5_checksum_recv, MD5_DIGEST_LENGTH);

    printf("MD5 for Sent File : ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        printf("%02x", md5_checksum_recv[i]);

    printf("\n");

    // verify
    if ((strncmp(md5_checksum, md5_checksum_recv, MD5_DIGEST_LENGTH)) == 0) {
        printf("MD5 Matched. File transfer was successful.\n");
    } else {
        printf("MD5 Not Matched. File transfer failed.\n");
    }
}

void transfer(int sockfd) {
    while (1) {
        bzero(buffer, MAX_SIZE);
        printf("Enter filename to send to server (\"exit\" to quit) : ");
        n = 0;

        // Copy filename into buffer
        while ((buffer[n++] = getchar()) != '\n');

        buffer[n - 1] = '\0';

        if ((strncmp(buffer, "exit", 4)) == 0) {
            //send the exit to the server
            write(sockfd, buffer, sizeof(buffer));
            printf("client is quitting...\n");
            break;
        }

        fp = fopen(buffer, "rb");
        if (fp == NULL) {
            printf("%s can't be opened.\n", buffer);
            continue;
        }

        //send the filename and filesize to the server
        write(sockfd, buffer, sizeof(buffer));
        fseek(fp, 0, SEEK_END);
        n = ftell(fp);
        rewind(fp);
        write(sockfd, & n, sizeof(int));

        bzero(buffer, MAX_SIZE);
        // get acknowledgement from the server that filename is received
        read(sockfd, buffer, sizeof(buffer));
        printf("Message From Server: %s\n", buffer);

        bzero(buffer, MAX_SIZE);

        calculate_md5_and_check(sockfd);
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