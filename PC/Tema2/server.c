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
int send_close_message(int socket, fd_set *read_fds) {
    struct message_info m;
    m.msg.type = CLOSE_CLIENT;

    int ret = send(socket, &m, sizeof(m), 0);
    if (ret < 0) return -1;

    ret = close(socket); 
    if(ret < 0) return -1;

    FD_CLR(socket, read_fds);
    return 0;
}

/**
 * @brief  Handles commands received from clients
 * @note   
 * @param  socket: the socket where the command came from
 * @param  *connected_clients: list of connected clients
 * @param  *disconnected_clients: list of disconnected clients
 * @param  *read_fds: set of descriptors
 * @retval None
 */
void handle_client_command(int socket, list *connected_clients, list *disconnected_clients, fd_set *read_fds) {
    // Initialize and receive the command
    struct client_command_info command;
    memset(&command, 0, sizeof(command));
    int count = recv(socket, &command, sizeof(command), 0);
    DIE(count < 0, "recv");

    if (command.type == SEND_ID) {
        // Client sends an id

        // Check if a client already has that id.
        struct client_info *client_by_id = search(*connected_clients, command.un.id, client_has_id);
        if (client_by_id != NULL) {
            printf("Client %s already connected.\n", command.un.id);
            send_close_message(socket, read_fds);
        } else {
            struct client_info *client_by_socket = search(*connected_clients, &socket, client_has_socket);
            strcpy(client_by_socket->id, command.un.id);
            char *ip = inet_ntoa((struct in_addr){client_by_socket->socket_info.sin_addr.s_addr});
            printf("New client %s connected from %s:%d\n", client_by_socket->id, ip, client_by_socket->socket_info.sin_port);

            // Check if the client had already connected once in the past
            struct client_info *old_client = search(*disconnected_clients, command.un.id, client_has_id);
            if (old_client != NULL) {
                // Copy the socket information from the old entry to the new one
                client_by_socket->subscriptions = old_client->subscriptions;
                client_by_socket->sf_messages = old_client->sf_messages;

                // Remove the client from disconnected_clients
                remove_node(disconnected_clients, old_client);
                free(old_client);
            }
        }
    } else if (command.type == EXIT) {
        // Clients wants to close the connection.
        struct client_info *client = search(*connected_clients, &socket, client_has_socket);
        printf("Client %s disconnected.\n", client->id);

        remove_node(connected_clients, client);

        int ret = insert(disconnected_clients, client);
        DIE(ret == 0, "insert");

        ret = close(socket); 
        DIE(ret < 0, "close");

        FD_CLR(socket, read_fds);
    } else if (command.type == SUBSCRIBE) {
        // Get the client
        struct client_info *client = search(*connected_clients, &socket, client_has_socket);
        DIE(client == NULL, "subscribe");

        // Create the subscription
        struct subscription_info *sub = malloc(sizeof(struct subscription_info));
        strncpy(sub->topic, command.un.sub_info.topic, TOPIC_LENGTH);
        sub->sf = command.un.sub_info.sf;

        // Insert the subscription
        insert(&client->subscriptions, sub);
    } else if (command.type == UNSUBSCRIBE) {
        // Get the client
        struct client_info *client = search(*connected_clients, &socket, client_has_socket);
        DIE(client == NULL, "unsubscribe");

        // Search for the subscription
        struct subscription_info *sub = search(client->subscriptions, command.un.sub_info.topic, subscription_has_topic);
        if (sub == NULL) {
            fprintf(stderr, "Subscription does not exist!\n");
            return;
        }

        // Remove the subscription
        remove_node(&client->subscriptions, sub);
    }

}

int send_message_to (int socket, struct message_info *msg_info) {
    int ret = send(socket, msg_info, sizeof(*msg_info), 0);
    if (ret < 0) return -1;
    return 0;
}

void handle_received_message(struct message_info *msg_info, list connected_clients, list disconnected_clients) {
    for (list p = connected_clients; p != NULL; p = p->next) {
        struct client_info *client = p->info;
        if (client_subscribed_to(client, msg_info->msg.topic)) {
            int ret = send_message_to(client->socket, msg_info);
            DIE(ret < 0, "send_message_to");
        }
    }
}

int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    if (argc != 2) {
        fprintf(stderr, "Usage: ./server PORT\n");
        exit(1);
    }

    int port = (int)strtol(argv[1], NULL, 0);
    if (port == 0) {
        fprintf(stderr, "Invalid port!\n");
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

    list connected_clients = NULL;
    list disconnected_clients = NULL;

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
                    fgets(buffer, sizeof(buffer), stdin);
                    if (strncmp(buffer, "exit", 4) == 0) {
                        goto end;
                    } else {
                        fprintf(stderr, "Invalid input!\n");
                    }
                } else if (i == udp_fd) {
                    // Incoming data from udp socket
                    struct message_info *msg_info = receive_message(udp_fd);
                    DIE(msg_info == NULL, "receive_message");
                    handle_received_message(msg_info, connected_clients, disconnected_clients);

                } else if (i == tcp_fd) {
                    struct client_info *new_client = accept_new_client(tcp_fd);
                    DIE(new_client == NULL, "accept_new_client");

                    int ret = insert(&connected_clients, new_client);
                    DIE(ret == 0, "insert");

                    if (new_client->socket > fdmax) fdmax = new_client->socket;
                    FD_SET(new_client->socket, &read_fds);
                } else {
                    // Command received from client
                    handle_client_command(i, &connected_clients, &disconnected_clients, &read_fds);
                }
            }
        }
    }

end:
    for (list p = connected_clients; p != NULL; p = p->next) {
        struct client_info *client = p->info;
        send_close_message(client->socket, &read_fds);
    }
    close(udp_fd);
    return 0;
}