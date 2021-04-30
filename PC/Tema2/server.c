#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <string.h>

#include "utils.h"

int init_udp_listener(int port) {

    // Initialize a sockaddr_in
    struct sockaddr_in udp_sockaddr;
    memset(&udp_sockaddr, 0, sizeof(udp_sockaddr));
    
    udp_sockaddr.sin_family = AF_INET;
    udp_sockaddr.sin_port = htons(port);
    udp_sockaddr.sin_addr.s_addr = INADDR_ANY;

    // Create the socket
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    DIE(sock == -1, "udp_socket");

    // Bind a port to the socket
    int ret = bind(sock, (const struct sockaddr *)&udp_sockaddr, sizeof(udp_sockaddr));
    DIE(ret == -1, "udp_bind");

    return sock;
}

int main(int argc, char **argv) {
    
    if (argc != 2) {
        printf ("Usage: ./server PORT\n");
        exit(1);
    }

    char buffer[BUFLEN];
    int udp_fd = init_udp_listener(atoi(argv[1]));
    

    while(1) {
        ssize_t count = recvfrom(udp_fd, buffer, BUFLEN, 0, NULL, NULL);
        DIE(count == -1, "recvrrom");

        printf("Primit mesaj: %s\n", buffer);
    }
    return 0;
}