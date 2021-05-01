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

#include "udp.h"
#include "utils.h"
#include "message.h"



int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    if (argc != 2) {
        fprintf(stderr, "Usage: ./server PORT\n");
        exit(1);
    }

    // Initialize descriptor sets
    int fdmax;
    fd_set read_fds;
    fd_set tmp_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&tmp_fds);

    FD_SET(STDIN_FILENO, &read_fds); // Add stdin into set

    int udp_fd = init_udp_listener(atoi(argv[1]));
    DIE(udp_fd == -1, "init_udp_listener");
    
    FD_SET(udp_fd, &read_fds);  // Add udp_fd into set
    fdmax = udp_fd; // Update the biggest file descriptor

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
                    scanf("%s", buffer);

                    if (strcmp(buffer, "exit") == 0) {
                        goto end;
                    } else {
                        fprintf(stderr, "Invalid input!\n");
                    }
                } else if (i == udp_fd) {
                    // Incoming data from udp socket
                    struct message *msg = recieve_message(udp_fd);
                    DIE(msg == NULL, "receive_message");

                    printf ("Primit mesaj: %s\n", msg->topic);
                }
            }
        }
    }

end:
    close(udp_fd);
    return 0;
}