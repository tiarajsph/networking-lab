#include <sys/socket.h>   // for socket(), connect(), send()
#include <netinet/in.h>   // for sockaddr_in structure
#include <stdio.h>        // for printf(), fgets()
#include <string.h>       // for string operations
#include <stdlib.h>       // for general utilities
#include <unistd.h>       // for close()

/*
This program implements a TCP client.

Steps performed:
1. Create a socket
2. Define server address
3. Connect to the server
4. Send data to the server
5. Close the socket
*/

int main()
{
    char buf[100];        // buffer to store message entered by user
    int k;                // variable to store return values of system calls
    int sock_desc;        // socket descriptor (unique id for the socket)

    struct sockaddr_in client;   // structure to store server address details


    /*
    Step 1: Create a socket

    AF_INET   -> IPv4 address family
    SOCK_STREAM -> TCP protocol
    0         -> default protocol
    */

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_desc == -1)
        printf("Error in socket creation!");


    /*
    Step 2: Configure server address

    sin_family -> address family (IPv4)
    sin_addr.s_addr -> IP address
    sin_port -> port number
    */

    client.sin_family = AF_INET;

    /*
    INADDR_ANY means connect to any available address
    (typically used for servers, but used here in simple lab programs)
    */

    client.sin_addr.s_addr = INADDR_ANY;

    /*
    Port number where server is listening
    */

    client.sin_port = 3003;


    /*
    Step 3: Connect to the server
    */

    k = connect(sock_desc, (struct sockaddr *)&client, sizeof(client));

    if (k == -1)
        printf("Error in connecting to server!");


    /*
    Step 4: Get message from user
    */

    printf("\nEnter data to be send: ");

    fgets(buf, 100, stdin);   // read message from keyboard


    /*
    Step 5: Send message to server
    */

    k = send(sock_desc, buf, 100, 0);

    if (k == -1)
        printf("Error in sending!");


    /*
    Step 6: Close the socket connection
    */

    close(sock_desc);

    return 0;
}