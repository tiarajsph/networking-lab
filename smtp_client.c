#include <stdio.h>      // printf(), fgets()
#include <string.h>     // strcpy(), strlen(), strchr()
#include <stdlib.h>     // general utilities
#include <unistd.h>     // close()
#include <arpa/inet.h>  // socket structures and networking functions

#define BUF_SIZE 256    // maximum buffer size for messages

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
    Structure to store server address information
    */
    struct sockaddr_in server;

    socklen_t server_len = sizeof(server);

    char buffer[BUF_SIZE];   // buffer for sending/receiving messages


    /*
    Configure server address
    */
    server.sin_family = AF_INET;                     // IPv4
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // server IP (localhost)
    server.sin_port = htons(8080);                   // server port


    /*
    STEP 1: Greeting
    Client sends greeting message to server
    */

    strcpy(buffer, "hi");

    sendto(sockfd, buffer, strlen(buffer)+1, 0,
           (struct sockaddr *)&server, server_len);

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&server, &server_len);

    printf("Server: %s\n", buffer);


    /*
    STEP 2: HELO command
    */

    strcpy(buffer, "HELO 127.0.0.1");

    sendto(sockfd, buffer, strlen(buffer)+1, 0,
           (struct sockaddr *)&server, server_len);

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&server, &server_len);

    printf("Server: %s\n", buffer);


    /*
    STEP 3: MAIL FROM command
    Client enters sender email address
    */

    printf("Enter FROM address: ");
    fgets(buffer, BUF_SIZE, stdin);

    // remove newline character
    buffer[strcspn(buffer, "\n")] = 0;

    char mail_from[BUF_SIZE];

    // create SMTP command
    snprintf(mail_from, BUF_SIZE, "MAIL FROM %s", buffer);

    sendto(sockfd, mail_from, strlen(mail_from)+1, 0,
           (struct sockaddr *)&server, server_len);

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&server, &server_len);

    printf("Server: %s\n", buffer);


    /*
    STEP 4: RCPT TO command
    Client enters receiver email address
    */

    printf("Enter TO address: ");
    fgets(buffer, BUF_SIZE, stdin);

    buffer[strcspn(buffer, "\n")] = 0;

    char rcpt_to[BUF_SIZE];

    snprintf(rcpt_to, BUF_SIZE, "RCPT TO %s", buffer);

    sendto(sockfd, rcpt_to, strlen(rcpt_to)+1, 0,
           (struct sockaddr *)&server, server_len);

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&server, &server_len);

    printf("Server: %s\n", buffer);


    /*
    STEP 5: DATA command
    Tells server that message body will be sent next
    */

    strcpy(buffer, "DATA");

    sendto(sockfd, buffer, strlen(buffer)+1, 0,
           (struct sockaddr *)&server, server_len);

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&server, &server_len);

    printf("Server: %s\n", buffer);


    /*
    STEP 6: Send email body
    */

    printf("Enter mail body (end with $): ");

    char mail_body[BUF_SIZE];

    fgets(mail_body, BUF_SIZE, stdin);

    /*
    Remove '$' symbol which indicates end of message
    */
    char *dollar = strchr(mail_body, '$');

    if (dollar)
        *dollar = '\0';

    sendto(sockfd, mail_body, strlen(mail_body)+1, 0,
           (struct sockaddr *)&server, server_len);


    /*
    STEP 7: QUIT command
    */

    strcpy(buffer, "QUIT");

    sendto(sockfd, buffer, strlen(buffer)+1, 0,
           (struct sockaddr *)&server, server_len);

    recvfrom(sockfd, buffer, BUF_SIZE, 0,
             (struct sockaddr *)&server, &server_len);

    printf("Server: %s\n", buffer);


    /*
    Close socket connection
    */

    close(sockfd);

    return 0;
}