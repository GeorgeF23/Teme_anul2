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

    int udp_fd = init_udp_listener(atoi(argv[1]));
    DIE(udp_fd == -1, "init_udp_listener");
    
    while(1) {
        struct message *msg = recieve_message(udp_fd);
        DIE(msg == NULL, "receive_message");

        printf ("Primit mesaj: %s\n", msg->topic);
    }
    return 0;
}