/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 3 
filename : udp_server.c
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
#define CHUNK_SIZE 1024
#define flag 0
#define timeout 1

typedef struct packet {
    int seq_num;
    int length;
    char data[CHUNK_SIZE];
}
Packet;

char buffer[CHUNK_SIZE];
char filename[CHUNK_SIZE] = "temp_";
Packet recv_from_client;
FILE * fp;
struct sockaddr_in serv_addr;
int len;

void calculate_md5_and_send(int sockfd) {
    int nBytes;

    fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("%s not found!\n", filename);
        exit(1);
    }

    // calculate MD5 checksum for original file
    unsigned char md5_checksum[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext;

    MD5_Init( & mdContext);
    nBytes = fread(buffer, 1, sizeof(buffer), fp);
    while (nBytes > 0) {
        MD5_Update( & mdContext, buffer, nBytes);
        bzero(buffer, CHUNK_SIZE);
        nBytes = fread(buffer, 1, sizeof(buffer), fp);
    }

    MD5_Final(md5_checksum, & mdContext);
    nBytes = sendto(sockfd, md5_checksum, MD5_DIGEST_LENGTH, flag, (struct sockaddr * ) & serv_addr, len);

    fclose(fp);
}

int main() {
    int e;

    fd_set readfds, masterfds;
    int sockfd, nBytes, fileSize, num_chunks;
    len = sizeof(serv_addr);

    bzero( & serv_addr, sizeof(serv_addr));

    // assign IP, PORT 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    // Create and Verify socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    e = bind(sockfd, (struct sockaddr * ) & serv_addr, sizeof(serv_addr));
    if (e == 0)
        printf("\nSuccessfully binded!\nServer running...\n");
    else
        printf("\nBinding Failed!\n");

    FD_ZERO( & masterfds); //reset masterfdset
    FD_ZERO( & readfds); //reset readfdset

    // add sockfd to masterfds
    FD_SET(sockfd, & masterfds);

    //set recv timeout value = 1sec
    struct timeval read_timeout;
    read_timeout.tv_sec = timeout;
    read_timeout.tv_usec = 0;

    while (1) {
        printf("Waiting to recieve from client... \n");
        bzero(buffer, CHUNK_SIZE);

        nBytes = recvfrom(sockfd, buffer, CHUNK_SIZE, flag, (struct sockaddr * ) & serv_addr, & len);

        nBytes = recvfrom(sockfd, & fileSize, sizeof(int), flag, (struct sockaddr * ) & serv_addr, & len);

        nBytes = recvfrom(sockfd, & num_chunks, sizeof(int), flag, (struct sockaddr * ) & serv_addr, & len);

        printf("\n Recieved Filename : %s\n", buffer);
        printf("Filesize: %d bytes arriving in total %d packets\n", fileSize, num_chunks);

        strcpy(filename + 5, buffer);

        fp = fopen(filename, "wb");

        if (fp == NULL) {
            printf("%s can't be opened.\n", filename);
            exit(1);
        }

        while (num_chunks--) {
            readfds = masterfds;
            fileSize = select(sockfd + 1, & readfds, NULL, NULL, & read_timeout);

            if (fileSize < 0) {
                perror("On select");
                exit(1);
            } else if (fileSize == 0) {
                // timeout for 1 sec
                printf("Timeout!\n");
            } else {
                if (FD_ISSET(sockfd, & readfds)) {
                    nBytes = recvfrom(sockfd, & recv_from_client, sizeof(Packet), flag, (struct sockaddr * ) & serv_addr, & len);
                    fwrite(recv_from_client.data, 1, recv_from_client.length, fp);
                    printf("Sequence Number : %d received\n", recv_from_client.seq_num);
                }
            }
        }

        fclose(fp);

        calculate_md5_and_send(sockfd);

    }
    close(sockfd);
    return 0;
}