#ifndef _CLIENT_H
#define _CLIENT_H 1

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

#include "list.h"
#include "message.h"

#define MAX_CLIENT_ID_LEN 11


#define SEND_ID 1
#define SUBSCRIBE 2
#define UNSUBSCRIBE 3
#define EXIT 4

/* Contains all the information about a client */
struct client_info {
    int socket;
    char id[MAX_CLIENT_ID_LEN];

    struct sockaddr_in socket_info;
    socklen_t socket_info_len;

    list sf_messages;
    list subscriptions;
};

/* Contains the information of a client command to the server */
struct client_command_info {
    uint8_t type;   // subscribe / unsubscribe / exit
    
    union {
        char id[MAX_CLIENT_ID_LEN];
        struct subscription_info sub_info;
    } un;
} __attribute__((packed));

/**
 * @brief  Checks if a client has a specific socket attached
 * @note   This function is used to search for a client in a list by his socket
 * @param  *client: the client
 * @param  *socket: the socket
 * @retval 1 if true / 0 if false
 */
int client_has_socket(void *client, void *socket);

/**
 * @brief  Checks if a client has a specific id
 * @note   This function is used to search for a client in a list by his id
 * @param  *client: the client
 * @param  *id: the id
 * @retval 1 if true / 0 if false
 */
int client_has_id(void *client, void *id);

#endif