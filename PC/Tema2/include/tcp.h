#ifndef _TCP_H
#define _TCP_H 1

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include "utils.h"
#include "message.h"

#define MAX_CLIENTS 1000
#define MAX_CLIENT_ID_LEN 11

struct client_info {
    int socket;
    char id[MAX_CLIENT_ID_LEN];

    struct sockaddr_in socket_info;
    socklen_t socket_info_len;
};

/**
 * @brief  Creates a tcp socket that listens for new connections
 * @note   
 * @param  port: the port to listen on
 * @retval the newly crated socket / -1 on error
 */
int init_tcp_listener(int port);

int accept_new_client(int fd);
#endif