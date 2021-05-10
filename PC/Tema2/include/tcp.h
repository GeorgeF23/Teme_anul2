#ifndef _TCP_H
#define _TCP_H 1

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/tcp.h>

#include "utils.h"
#include "message.h"
#include "subscriber.h"

#define MAX_CLIENTS 1000

/**
 * @brief  Creates a tcp socket that listens for new connections
 * @note   
 * @param  port: the port to listen on
 * @retval the newly crated socket / -1 on error
 */
int init_tcp_listener(int port);

/**
 * @brief  Registers a new client
 * @note   At this point the id of the client is unknown. The client needs to send another message with his id
 * @param  fd: the tcp listenet socket
 * @retval the information about the new client / NULL on error
 */
struct client_info *accept_new_client(int fd);
#endif