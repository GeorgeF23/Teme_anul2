#include "udp.h"

int init_udp_listener(int port) {

    // Initialize a sockaddr_in
    struct sockaddr_in udp_sockaddr;
    memset(&udp_sockaddr, 0, sizeof(udp_sockaddr));
    
    udp_sockaddr.sin_family = AF_INET;
    udp_sockaddr.sin_port = htons(port);
    udp_sockaddr.sin_addr.s_addr = INADDR_ANY;

    // Create the socket
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1) return -1;

    // Bind a port to the socket
    int ret = bind(sock, (const struct sockaddr *)&udp_sockaddr, sizeof(udp_sockaddr));
    if (ret == -1) return -1;

    return sock;
}

struct message *recieve_message(int socket) {
    struct message *msg = malloc(sizeof(struct message));

    ssize_t count = recvfrom(socket, msg, MESSAGE_LENGTH, 0, NULL, NULL);
    if (count == -1) return NULL;

    return msg;
}