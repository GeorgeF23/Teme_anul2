#ifndef _SERVER_H
#define _SERVER_H 1

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
#include "subscriber.h"
#include "client.h"
#include "list.h"

/**
 * @brief  Sends a message to a subscriber telling him to shut down
 * @note   
 * @param  socket: the socket to send the message
 * @param  *read_fds: the set of descriptors
 * @retval 0 on success / -1 on error
 */
int send_close_message(int socket, fd_set *read_fds);

/**
 * @brief  Sends a message through a socket
 * @note   
 * @param  socket: the socket to send the message to
 * @param  *msg_info: the message information
 * @retval 0 on success / -1 on error
 */
int send_message_to(int socket, struct message_info *msg_info);

/**
 * @brief  Handles the store and forward feature
 * @note   This function is used when a client connects.
 *         It sends all the SF messages the client is subscribed with the SF flag to.
 * @param  *client: the client to send sf messages
 * @retval 0 on success / -1 on error
 */
int handle_sf_messages(struct client_info *client);

/**
 * @brief  Handles commands received from clients
 * @note   
 * @param  socket: the socket where the command came from
 * @param  *connected_clients: list of connected clients
 * @param  *disconnected_clients: list of disconnected clients
 * @param  *read_fds: set of descriptors
 * @retval None
 */
void handle_client_command(int socket, list *connected_clients, list *disconnected_clients, fd_set *read_fds);

/**
 * @brief  Handles an incoming message
 * @note   Sends the message to the connected clients that are subscribed to it
 *         Stores the message for the disconnected clients that are subscribed with SF to it
 * @param  *msg_info: the message information
 * @param  connected_clients: list of connected clients
 * @param  disconnected_clients: list of disconencted clients
 * @retval None
 */
void handle_received_message(struct message_info *msg_info, list connected_clients, list disconnected_clients);
#endif