#ifndef _UDP_H
#define _UDP_H 1

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include "utils.h"
#include "message.h"

/**
 * @brief  Creates an UDP socket and binds it to a port
 * @note   
 * @param  port: port of the UDP socket
 * @retval the newly crated socket / -1 on error
 */
int init_udp_listener(int port);

/**
 * @brief  Reads a message from an UDP socket
 * @note   
 * @param  socket: udp socket to read from
 * @retval the message that has been read / NULL on error
 */
struct message *recieve_message(int socket);

#endif