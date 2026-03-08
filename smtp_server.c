#include <stdio.h>      // printf(), perror()
#include <string.h>     // strcpy(), strlen()
#include <stdlib.h>     // standard utilities
#include <unistd.h>     // close()
#include <arpa/inet.h>  // socket structures and functions

#define BUF_SIZE 256    // maximum size of the message buffer

int main() {

    /*
    Create a UDP socket
    AF_INET   -> IPv4 addressing
    SOCK_DGRAM -> UDP protocol
    */
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1) {
        perror("socket");   // print error if socket creation fails
        return 1;
    }

    /*
    Structures to store server and client address information
    */
    struct sockaddr_in server, client;

    socklen_t client_len = sizeof(client);   // size of client structure

    char buffer[BUF_SIZE];   // buffer to store incoming messages


    /*
    Configure server address
    */
    server.sin_family = AF_INET;           // IPv4 address family
    server.sin_addr.s_addr = INADDR_ANY;   // accept packets from any IP
    server.sin_port = htons(8080);         // server port number (network byte order)


    /*
    Bind socket to the specified address and port
    */
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind");   // print error if binding fails
        return 1;
    }

    printf("Server waiting on port 8080...\n");


    /*
    STEP 1: Greeting from client
    Server receives greeting message and responds with SMTP greeting
    */

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&client, &client_len);

    printf("Client: %s\n", buffer);

    strcpy(buffer, "220 127.0.0.1");   // server greeting response

    sendto(sockfd, buffer, strlen(buffer)+1, 0,
           (struct sockaddr *)&client, client_len);


    /*
    STEP 2: HELO command
    */

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&client, &client_len);

    printf("Client: %s\n", buffer);

    sendto(sockfd, "250 ok", 7, 0,
           (struct sockaddr *)&client, client_len);


    /*
    STEP 3: MAIL FROM command
    */

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&client, &client_len);

    printf("Client: %s\n", buffer);

    sendto(sockfd, "250 ok", 7, 0,
           (struct sockaddr *)&client, client_len);


    /*
    STEP 4: RCPT TO command
    */

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&client, &client_len);

    printf("Client: %s\n", buffer);

    sendto(sockfd, "250 ok", 7, 0,
           (struct sockaddr *)&client, client_len);


    /*
    STEP 5: DATA command
    Server tells client to start sending message body
    */

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&client, &client_len);

    printf("Client: %s\n", buffer);

    sendto(sockfd, "354 Go ahead", 13, 0,
           (struct sockaddr *)&client, client_len);


    /*
    STEP 6: Receive email message body
    */

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&client, &client_len);

    printf("Mail body: %s\n", buffer);


    /*
    STEP 7: QUIT command
    */

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&client, &client_len);

    printf("Client: %s\n", buffer);

    sendto(sockfd, "221 OK", 7, 0,
           (struct sockaddr *)&client, client_len);


    /*
    Close the socket
    */
    close(sockfd);

    return 0;
}