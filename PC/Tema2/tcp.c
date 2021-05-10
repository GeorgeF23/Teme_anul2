#include "tcp.h"

int init_tcp_listener(int port) {
    // Initialize a sockaddr_in
    struct sockaddr_in tcp_sockaddr;
    memset(&tcp_sockaddr, 0, sizeof(tcp_sockaddr));
    
    tcp_sockaddr.sin_family = AF_INET;
    tcp_sockaddr.sin_port = htons(port);
    tcp_sockaddr.sin_addr.s_addr = INADDR_ANY;

    // Create the tcp socket
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) return -1;

    // Bind the port to the socket
    int ret = bind(sock, (const struct sockaddr *)&tcp_sockaddr, sizeof(tcp_sockaddr));
    if (ret == -1) return -1;

    // Set the socket as a listener for new connections
    ret = listen(sock, MAX_CLIENTS);
	if (ret == -1) return -1;

    return sock;
}

struct client_info *accept_new_client(int fd) {
    struct client_info *client = malloc(sizeof(struct client_info));
    if (client == NULL) return NULL;

    client->socket_info_len = sizeof(struct sockaddr_in);

    int client_socket = accept(fd, (struct sockaddr *) &client->socket_info, &client->socket_info_len);
    if (client_socket < 0) return NULL;

    // Disable Neagle
    int flag = 1;
    int result = setsockopt(client_socket, IPPROTO_TCP, TCP_NODELAY, (char *) &flag,  sizeof(int));
    if (result < 0) return NULL;

    client->socket = client_socket;
    memset(client->id, 0, MAX_CLIENT_ID_LEN);
    client->subscriptions = NULL;
    client->sf_messages = NULL;

    return client;
}