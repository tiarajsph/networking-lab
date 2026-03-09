#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char buf[100];
    int k;
    socklen_t len;

    int sock_desc;
    struct sockaddr_in server, client;

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc == -1)
        printf("Error in socket creation!");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2000);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(2000);

    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
        printf("Error in binding!");

    len = sizeof(client);

    printf("Server waiting...\n");

    k = recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&client, &len);
    if (k == -1)
        printf("Error in receiving!");

    printf("Message got from client: %s", buf);

    close(sock_desc);

    return 0;
}
