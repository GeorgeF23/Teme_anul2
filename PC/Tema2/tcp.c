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

int accept_new_client(int fd) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int client_socket = accept(fd, (struct sockaddr *) &client_addr, &client_addr_len);
    if (client_socket < 0) return -1;

    return client_socket;
}