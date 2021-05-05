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

#include "udp.h"
#include "tcp.h"



int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    if (argc != 2) {
        fprintf(stderr, "Usage: ./server PORT\n");
        exit(1);
    }

    int port = (int)strtol(argv[1], NULL, 0);
    if (port == 0) {
        fprintf(stderr, "Invalid port!");
        exit(2);
    }

    // Initialize descriptor sets
    int fdmax;
    fd_set read_fds;
    fd_set tmp_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&tmp_fds);

    int udp_fd = init_udp_listener(port);
    DIE(udp_fd == -1, "init_udp_listener");

    int tcp_fd = init_tcp_listener(port);
    DIE(tcp_fd == -1, "init_tcp_listener");
    
    FD_SET(STDIN_FILENO, &read_fds); // Add stdin into set
    FD_SET(udp_fd, &read_fds);  // Add udp_fd into set
    FD_SET(tcp_fd, &read_fds);  // Add tcp_fd into set
    fdmax = (tcp_fd > udp_fd) ? tcp_fd : udp_fd; // Update the biggest file descriptor

    while(1) {
        tmp_fds = read_fds; // Create copy of fd set

        // Get the fd's with incoming data
        int ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
        DIE(ret < 0, "select");

        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &tmp_fds)) {
                if (i == STDIN_FILENO) {
                    // Incoming data from stdin
                    char buffer[16];
                    fgets(buffer, 16, stdin);
                    if (strncmp(buffer, "exit", 4) == 0) {
                        goto end;
                    } else {
                        fprintf(stderr, "Invalid input!\n");
                    }
                } else if (i == udp_fd) {
                    // Incoming data from udp socket
                    struct message *msg = recieve_message(udp_fd);
                    DIE(msg == NULL, "receive_message");

                    printf ("Primit mesaj: %s\n", msg->topic);
                } else if (i == tcp_fd) {
                    int new_client_fd = accept_new_client(tcp_fd);
                    DIE(new_client_fd == -1, "accept_new_client");

                    printf("Client nou la socket: %d\n", new_client_fd);
                }
            }
        }
    }

end:
    close(udp_fd);
    return 0;
}