#ifndef _SUBSCRIBER_H
#define _SUBSCRIBER_H 1

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "list.h"
#include "message.h"
#include "utils.h"
#include "client.h"


/**
 * @brief  Connects the client to the server
 * @note   
 * @param  server_ip: ip address of server in network endianess
 * @param  server_port: port of server in host endianess
 * @retval newly created socket / -1 on error
 */
int connect_to_server(uint32_t server_ip, uint16_t server_port);

/**
 * @brief  Send client id to server
 * @note   
 * @param  socket: the socket to send the packet to
 * @param  *id: id of client
 * @retval 0 on success / -1 on error
 */
int send_id_to_server(int socket, char *id);

/**
 * @brief  Send a subscribe command to the server
 * @note   
 * @param  socket: the socket to send the command to
 * @param  *topic: the topic to subscribe to
 * @param  sf: sf parameter
 * @retval 0 on success / -1 on error
 */
int send_subscribe_to_server(int socket, char *topic, int sf);

/**
 * @brief  Send an unsubscribe command to the server
 * @note   
 * @param  socket: the socket to send the command to
 * @param  *topic: the topic to unsubscribe from
 * @retval 0 on success / -1 on error
 */
int send_unsubscribe_to_server(int socket, char *topic);

/**
 * @brief  Parses and prints a message
 * @note   
 * @param  msg_info: the message
 * @retval None
 */
void print_message(struct message_info msg_info);
#endif