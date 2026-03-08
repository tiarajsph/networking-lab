#include <sys/socket.h>   // for socket(), bind(), listen(), accept(), recv()
#include <netinet/in.h>   // for sockaddr_in structure
#include <stdio.h>        // for printf()
#include <string.h>       // for string operations
#include <stdlib.h>       // for general utilities
#include <unistd.h>       // for close()

/*
This program implements a TCP server.

Steps performed:
1. Create a socket
2. Bind the socket to an address and port
3. Listen for incoming client connections
4. Accept a client connection
5. Receive data from the client
6. Display the received message
7. Close the connection
*/

int main()
{
    char buf[100];       // buffer to store message received from client
    int k;               // variable to store return values of system calls
    socklen_t len;       // variable to store size of client address

    int sock_desc;       // main socket descriptor (server socket)
    int temp_sock_desc;  // temporary socket descriptor for client connection

    struct sockaddr_in server, client;   // structures for server and client addresses


    /*
    Step 1: Create a socket

    AF_INET     -> IPv4 address family
    SOCK_STREAM -> TCP protocol
    0           -> default protocol
    */

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_desc == -1)
        printf("Error in socket creation");


    /*
    Step 2: Configure server address
    */

    server.sin_family = AF_INET;          // IPv4
    server.sin_addr.s_addr = INADDR_ANY;  // accept connection from any IP
    server.sin_port = 3003;               // port number


    /*
    Client structure is used to store details
    about the connecting client
    */

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = 3003;


    /*
    Step 3: Bind the socket

    This attaches the socket to a specific port
    */

    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));

    if (k == -1)
        printf("Error in binding");


    /*
    Step 4: Listen for incoming client connections

    The number 5 represents the backlog queue size
    (maximum pending connections).
    */

    k = listen(sock_desc, 5);

    if (k == -1)
        printf("Error in listening");


    /*
    Step 5: Accept a connection from a client

    accept() creates a new socket dedicated to the client.
    */

    len = sizeof(client);

    temp_sock_desc = accept(sock_desc, (struct sockaddr *)&client, &len);

    if (temp_sock_desc == -1)
        printf("Error in temporary socket creation");


    /*
    Step 6: Receive message from client
    */

    k = recv(temp_sock_desc, buf, 100, 0);

    if (k == -1)
        printf("Error in receiving");


    /*
    Step 7: Display received message
    */

    printf("Message got from client: %s", buf);


    /*
    Step 8: Close the client socket
    */

    close(temp_sock_desc);

    return 0;
}