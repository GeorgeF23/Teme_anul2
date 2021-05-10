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

struct message_info *receive_message(int socket) {
    struct message_info *msg_info = malloc(sizeof(struct message_info));
    struct sockaddr_in udp_info;
    socklen_t len = sizeof(udp_info);

    ssize_t count = recvfrom(socket, &msg_info->msg, sizeof(msg_info->msg), 0, (struct sockaddr *)&udp_info, &len);
    if (count == -1) return NULL;

    strcpy(msg_info->source_ip, inet_ntoa(udp_info.sin_addr));
    msg_info->source_port = htons(udp_info.sin_port);

    return msg_info;
}