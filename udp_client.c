#include <sys/socket.h>   // for socket(), sendto()
#include <netinet/in.h>   // for sockaddr_in structure
#include <stdio.h>        // for printf(), fgets()
#include <string.h>       // for string functions
#include <stdlib.h>       // for atoi()

/*
This program implements a UDP client.

Steps performed:
1. Create a UDP socket
2. Specify the server address and port
3. Read a message from the user
4. Send the message to the server using sendto()
*/

int main(int argc, char *argv[])
{
    // structures to store server and client address information
    struct sockaddr_in server, client;

    /*
    The program expects command line arguments.

    argc should be 3:
    argv[0] -> program name
    argv[1] -> server IP (not used here in this simple program)
    argv[2] -> port number

    Example execution:
    ./client 127.0.0.1 3003
    */

    if (argc != 3)
        printf("Input format not correct!\n");


    /*
    Step 1: Create a socket

    AF_INET     -> IPv4
    SOCK_DGRAM  -> UDP protocol
    0           -> default protocol
    */

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
        printf("Error in socket creation!\n");


    /*
    Step 2: Configure server address
    */

    server.sin_family = AF_INET;        // IPv4 address family

    /*
    INADDR_ANY allows communication with any address
    (in real applications client usually specifies server IP)
    */

    server.sin_addr.s_addr = INADDR_ANY;

    /*
    Port number is taken from command line argument
    atoi() converts string → integer
    htons() converts host byte order → network byte order
    */

    server.sin_port = htons(atoi(argv[2]));


    /*
    Buffer to store message entered by user
    */

    char buffer[100];

    /*
    Step 3: Read message from keyboard
    */

    printf("Enter a message to sent to server: ");

    fgets(buffer, 100, stdin);


    /*
    Step 4: Send message to server

    sendto() is used in UDP because there is no connection
    between client and server.
    */

    if (sendto(sockfd, buffer, sizeof(buffer), 0,
               (struct sockaddr *)&server, sizeof(server)) < 0)
        printf("Error in sending!\n");

    return 0;
}