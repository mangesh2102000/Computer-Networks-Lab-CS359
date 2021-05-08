/*  Name: Chandrawanshi Mangesh Shivaji
	Roll No.: 1801CS16
	CS359 Assignment 4: Implement a Peer-to-Peer Chat Application
	Filename: p2pchat.c
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/select.h>

#define MAX_SIZE 2048

typedef struct USER {
    char name[105];
    char ip[16];
    int port;
}
USER;

// Function to read and store all users data from users.txt 
void initialize_user_table(USER * users_info) {

    FILE * fp = fopen("users.txt", "r");

    if (fp == NULL) {
        printf("users.txt can't be opened.\n");
        exit(1);
    }

    printf("---ALL USERS INFO----(format: name ip port)\n");
    for (int i = 0; i < 5; i++) {
        fscanf(fp, "%s %s %d", users_info[i].name, users_info[i].ip, & (users_info[i].port));
        printf("%s %s %d\n", users_info[i].name, users_info[i].ip, users_info[i].port);
    }
    printf("---------------------\n\n");

    fclose(fp);
}

void check_input_validity(int argc)
{
	if (argc != 2) {
        printf("Invalid Input!; Usage: ./p2p_chat <port_num>\n");
        exit(1);
    }
}

void check_socket_creation(int sockfd)
{
	if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
}

// Function to send msg from one peer to another
void send_msg(char * buffer, USER * users_info, int user_id) {
    char msg[MAX_SIZE], name[105];
    bzero(msg, MAX_SIZE);
    bzero(name, 105);

    // check msg format (friendname/msg)
    sscanf(buffer, "%[^/]%*c%[^\n]%*c", name, msg);

    if (strlen(msg) == 0) {
        printf("Invalid Message Format, Usage: <friendname>/<msg>\n");
        return;
    }

    // check if user with friendname exists or not 
    int check_name = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(name, users_info[i].name) == 0) {
            check_name = i;
            break;
        }
    }

    if (check_name == -1) {
        printf("User not found! Check users.txt\n");
        return;
    }

    // create new socket to connect with reciever using ip and port
    struct sockaddr_in servaddr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    check_socket_creation(sockfd);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(users_info[check_name].ip);
    servaddr.sin_port = htons(users_info[check_name].port);

    if (connect(sockfd, (struct sockaddr * ) & servaddr, sizeof(servaddr)) != 0) {
        printf("Error while establishing connection. Check if user is online or not\n");
        if (errno == ECONNREFUSED)
            return;
    }

    // send msg to the user
    sprintf(buffer, "%s: %s", users_info[user_id].name, msg);
    send(sockfd, buffer, MAX_SIZE, 0);
    printf("---Message Sent---\n");

    close(sockfd);
}

int main(int argc, char const * argv[]) {
	
	// call function to store user data 
    USER users_info[5];
    initialize_user_table(users_info);

    // valid input or not 
    check_input_validity(argc);

    // initial all required communication variables
    int servsock, peersock, maxfd, port, result;    
    struct sockaddr_in servaddr, clientaddr;
    int addrlen = sizeof(struct sockaddr);
    fd_set readfd, masterfd;

    port = atoi(argv[1]);
    servsock = socket(AF_INET, SOCK_STREAM, 0);

    // valid socket or not
    check_socket_creation(servsock);

    printf("[+]Server socket created successfully.\n");

    // check validity of input port number
    int flag = -1;
    for (int i = 0; i < 5; i++) {
        if (users_info[i].port == port) {
            printf("Welcome to p2p_chat, %s!\n", users_info[i].name);
            flag = i;
            break;
        }
    }

    if (flag == -1) {
        close(servsock);
        printf("port not found! Verify with users.txt\n");
        exit(1);
    }

    // set option to reuse port in case of program crash 
    int option_value = 1;
    setsockopt(servsock, SOL_SOCKET, SO_REUSEADDR, & option_value, sizeof(int));

    // initialize server side of the network
    bzero( & servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // bind the socket to server
    int e = bind(servsock, (struct sockaddr * ) & servaddr, sizeof(servaddr));
    if (e < 0) {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n");

    // max amount of parallel connections 
    if (listen(servsock, 5) == 0) {
        printf("[+]Listening....\n");
    } else {
        perror("[-]Error in listening");
        exit(1);
    }

    // masterfd will contain all the connected file descriptors 
    FD_ZERO( & masterfd);
    // add server to masterfd
    FD_SET(servsock, & masterfd);
    // add stdin to masterfd
    FD_SET(0, & masterfd);

    maxfd = servsock;
    printf("\nEnter msg to send <friendname>/<msg>.(Enter exit to quit)\n");

   	// buffer to store msg 
    char buffer[MAX_SIZE];
    int user_id = flag;
    while (1) {
    	// make copy of masterfd set and store it in temporary set(readfd)
    	memcpy(&readfd, &masterfd, sizeof(masterfd));

    	// monitor all fds < maxfd+1
        result = select(maxfd + 1, & readfd, NULL, NULL, NULL);

        if (result > 0) {

        	// if server socket fd is ready, accept incoming connections 
            if (FD_ISSET(servsock, & readfd)) {
                peersock = accept(servsock, (struct sockaddr * ) & clientaddr, & addrlen);
                if (peersock < 0) {
                    printf("Error in accepting a new connection\n");
                    exit(1);
                } else {
                    FD_SET(peersock, & masterfd);
                    if (peersock > maxfd) {
                        maxfd = peersock;
                    }
                }
                // remove server socket from readfd set 
                FD_CLR(servsock, & readfd);
            }

            // check if stdin is ready, if yes get input from user and send to msg / exit accordingly 
            if (FD_ISSET(0, & readfd)) {
                result = read(0, buffer, MAX_SIZE);
                if (result < 0) {
                    printf("Error : not able to read from stdin\n");
                    exit(1);
                }
                buffer[result] = '\0';
                if (strcmp("exit\n", buffer) == 0) {
                    close(servsock);
                    printf("user exits...\n");
                    exit(0);
                } else {
                    send_msg(buffer, users_info, user_id);
                }
            }

            // check connected peers and recieve messages if they are sent from any of them
            for (int i = 0; i < maxfd; i++) {
                if (FD_ISSET(i + 1, & readfd)) {
                    result = recv(i + 1, buffer, MAX_SIZE, 0);
                    if (result > 0) {
                        buffer[result] = '\0';
                        printf("%s", buffer);
                        printf("\n---------------------------\n\n");
                    } else if (result == 0) {
                        close(i + 1);
                        FD_CLR(i + 1, & masterfd);
                    } else {
                        printf("Error in receiving message\n");
                        exit(1);
                    }
                }
            }

        } else if (result < 0) {
            printf("Error on select()\n");
            exit(1);
        }
    }

    return 0;
}