#include <sys/socket.h>   // for socket(), bind(), recvfrom()
#include <netinet/in.h>   // for sockaddr_in structure
#include <stdio.h>        // for printf()
#include <string.h>       // for string handling
#include <stdlib.h>       // for atoi()

/*
This program implements a UDP server using socket programming.

Steps performed:
1. Create a socket
2. Configure server address
3. Bind the socket to a port
4. Wait for data from a client
5. Receive and display the message
*/

int main(int argc, char *argv[])
{
    struct sockaddr_in server, client;   // structures to store server and client addresses

    /*
    argc should be 2:
    argv[1] -> port number passed through command line
    Example: ./server 3003
    */

    if (argc != 2)
        printf("Input format not correct!\n");


    /*
    Step 1: Create a socket

    AF_INET     -> IPv4 address family
    SOCK_DGRAM  -> UDP protocol
    0           -> default protocol
    */

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
        printf("Error in socket creation!\n");


    /*
    Step 2: Configure server address
    */

    server.sin_family = AF_INET;          // IPv4 address family

    /*
    INADDR_ANY allows the server to accept packets
    from any network interface.
    */

    server.sin_addr.s_addr = INADDR_ANY;

    /*
    Convert port number from command line argument
    from string to integer using atoi()
    Then convert to network byte order using htons()
    */

    server.sin_port = htons(atoi(argv[1]));


    /*
    Step 3: Bind the socket to the specified port
    This associates the socket with the server address
    */

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
        printf("Error in bind()!\n");


    /*
    Buffer to store received message
    */

    char buffer[100];


    /*
    socklen_t is used to store address size
    */

    socklen_t server_len = sizeof(server);


    /*
    Server waits for incoming datagrams
    */

    printf("Server waiting...\n");


    /*
    Step 4: Receive message from client

    recvfrom() is used in UDP communication
    because UDP is connectionless.
    */

    if (recvfrom(sockfd, buffer, 100, 0, (struct sockaddr *)&server,
                 &server_len) < 0)
        printf("Error in receiving!\n");


    /*
    Step 5: Display received message
    */

    printf("Got a datagram: %s", buffer);

    return 0;
}