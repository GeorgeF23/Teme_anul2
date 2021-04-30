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
#include <math.h>

#include "utils.h"
#include "message.h"

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
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    if (argc != 2) {
        fprintf(stderr, "Usage: ./server PORT\n");
        exit(1);
    }

    struct message buffer;
    int udp_fd = init_udp_listener(atoi(argv[1]));
    
    while(1) {
        ssize_t count = recvfrom(udp_fd, &buffer, MESSAGE_LENGTH, 0, NULL, NULL);
        DIE(count == -1, "recvfrom");

        printf("Primit mesaj: %s; %d; ", buffer.topic, buffer.type);
        if (buffer.type == 0) {
            printf("%d %d", buffer.contents.int_info.sign, ntohl(buffer.contents.int_info.value));
        } else if (buffer.type == 1) {
            printf("%f", ((float)ntohs(buffer.contents.short_real_info.value)) / 100);
        } else if (buffer.type == 2) {
            float value = ((float)ntohl(buffer.contents.float_info.value)) / pow(10, buffer.contents.float_info.decimal_digits);
            printf("%f", value);
        } else if (buffer.type == 3) {
            printf("%s", buffer.contents.string_info.value);
        }

        printf("\n");
    }
    return 0;
}