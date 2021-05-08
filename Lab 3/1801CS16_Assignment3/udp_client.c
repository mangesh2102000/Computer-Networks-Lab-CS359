/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 3 
filename : udp_client.c
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <openssl/md5.h>

#define PORT 6032
#define CHUNK_SIZE 1024
#define flag 0

typedef struct packet {
    int seq_num;
    int length;
    char data[CHUNK_SIZE];
}
Packet;

FILE * fp;
Packet send_to_server;
char filename[CHUNK_SIZE];
char buffer[CHUNK_SIZE];
struct sockaddr_in serv_addr;
int len;

void calculate_md5_and_check(int sockfd) {
    int nBytes;

    fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("%s not found!\n", filename);
        exit(1);
    }

    unsigned char md5_checksum[MD5_DIGEST_LENGTH], md5_checksum_recv[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext;

    MD5_Init( & mdContext);
    nBytes = fread(buffer, 1, sizeof(buffer), fp);
    while (nBytes > 0) {
        MD5_Update( & mdContext, buffer, nBytes);
        bzero(buffer, CHUNK_SIZE);
        nBytes = fread(buffer, 1, sizeof(buffer), fp);
    }

    MD5_Final(md5_checksum, & mdContext);

    printf("MD5 for Original File : ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        printf("%02x", md5_checksum[i]);

    printf("\n");

    bzero(md5_checksum_recv, sizeof(md5_checksum_recv));

    nBytes = recvfrom(sockfd, md5_checksum_recv, MD5_DIGEST_LENGTH, flag, (struct sockaddr * ) & serv_addr, & len);

    printf("MD5 for Sent File : ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        printf("%02x", md5_checksum_recv[i]);

    printf("\n");

    if ((strncmp(md5_checksum, md5_checksum_recv, MD5_DIGEST_LENGTH)) == 0) {
        printf("MD5 Matched. File transfer was successful.\n");
    } else {
        printf("MD5 Not Matched. File transfer failed.\n");
    }

    fclose(fp);
}

int main() {
    char * ip = "127.0.0.1";

    int sockfd, nBytes, num_chunks;

    len = sizeof(serv_addr);
    bzero( & serv_addr, sizeof(serv_addr));

    // assign IP, PORT 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(PORT);

    // Create and Verify socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    while (1) {
        printf("Enter filename to send to server: \n");
        scanf("%s", buffer);

        fp = fopen(buffer, "rb");
        if (fp == NULL) {
            printf("%s can't be opened.\n", buffer);
            continue;
        }

        strcpy(filename, buffer);

        // get size of the file in bytes
        fseek(fp, 0, SEEK_END);
        nBytes = ftell(fp);
        rewind(fp);

        // calculate total number of chunks to send
        num_chunks = (nBytes + CHUNK_SIZE - 1) / CHUNK_SIZE;

        //sending filename, filesize and number of chunks to server
        sendto(sockfd, filename, CHUNK_SIZE, flag, (struct sockaddr * ) & serv_addr, len);

        sendto(sockfd, & nBytes, sizeof(int), flag, (struct sockaddr * ) & serv_addr, len);

        sendto(sockfd, & num_chunks, sizeof(int), flag, (struct sockaddr * ) & serv_addr, len);

        int curr_seqnum = 0;
        while (num_chunks--) {
            bzero( & send_to_server, sizeof(send_to_server));
            nBytes = fread(send_to_server.data, 1, CHUNK_SIZE, fp);
            curr_seqnum++;
            send_to_server.seq_num = curr_seqnum;
            send_to_server.length = nBytes;
            sendto(sockfd, & send_to_server, sizeof(send_to_server), flag, (struct sockaddr * ) & serv_addr, len);
        }
        printf("\nFILE SENT\n");

        fclose(fp);

        calculate_md5_and_check(sockfd);
    }
    close(sockfd);
    return 0;
}