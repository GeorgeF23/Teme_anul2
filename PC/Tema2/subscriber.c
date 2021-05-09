#include "subscriber.h"

int connect_to_server(uint32_t server_ip, uint16_t server_port) {
    // Create the socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return -1;

    // Initialize server details
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_port = htons(server_port);
    serv_addr.sin_addr.s_addr = server_ip;

    int ret = connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if (ret < 0) return -1;

    // Disable Neagle
    int flag = 1;
    ret = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag,  sizeof(int));
    if (ret < 0) return -1;

    return sock;
}

int send_id_to_server(int socket, char *id) {
    // Make the command
    struct client_command_info command;
    command.type = SEND_ID;
    strcpy(command.un.id, id);

    // Send the command
    int ret = send(socket, &command, sizeof(command), 0);
    if (ret < 0) return -1;
    return 0;
}

int send_subscribe_to_server(int socket, char *topic, int sf) {
    // Make the command
    struct client_command_info command;
    command.type = SUBSCRIBE;
    strcpy(command.un.sub_info.topic, topic);
    command.un.sub_info.sf = sf;

    // Send the command
    int ret = send(socket, &command, sizeof(command), 0);
    if (ret < 0) return -1;
    return 0;
}

int send_unsubscribe_to_server(int socket, char *topic) {
    // Make the command
    struct client_command_info command;
    command.type = UNSUBSCRIBE;
    strcpy(command.un.sub_info.topic, topic);

    // Send the command
    int ret = send(socket, &command, sizeof(command), 0);
    if (ret < 0) return -1;
    return 0;
}


int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    if (argc != 4) {
        fprintf(stderr, "Usage: ./subscriber ID IP_SERVER PORT_SERVER\n");
        exit(1);
    }

    // Parse arguments
    char id[MAX_CLIENT_ID_LEN];
    strcpy(id, argv[1]);

    uint16_t server_port = (int)strtol(argv[3], NULL, 0);
    if (server_port == 0) {
        fprintf(stderr, "Invalid port!\n");
        exit(2);
    }

    uint32_t server_ip = inet_addr(argv[2]);
    if (server_ip == (in_addr_t)(-1)) {
        fprintf(stderr, "Invalid IP!\n");
        exit(3);
    }

    // Initialize descriptor sets
    int fdmax;
    fd_set read_fds;
    fd_set tmp_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&tmp_fds);


    int tcp_socket = connect_to_server(server_ip, server_port);
    DIE(tcp_socket < 0, "connect_to_server");

    fdmax = tcp_socket;

    FD_SET(STDIN_FILENO, &read_fds); // Add stdin into set
    FD_SET(tcp_socket, &read_fds);  // Add the tcp socket into set

    // Send client id to server
    send_id_to_server(tcp_socket, id);

    while(1) {
        tmp_fds = read_fds; // Create copy of fd set

        // Get the fd's with incoming data
        int ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
        DIE(ret < 0, "select");

        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &tmp_fds)) {
                if (i == STDIN_FILENO) {
                    char buffer[100];
                    fgets(buffer, sizeof(buffer), stdin);

                    if (strncmp(buffer, "exit", 4) == 0) {
                        // Tell the server to close the socket
                        struct client_command_info command;
                        command.type = EXIT;

                        int ret = send(tcp_socket, &command, sizeof(command), 0);
                        DIE(ret < 0, "send");
                        goto end;
                    } else if (strncmp(buffer, "subscribe", 9) == 0){
                        char topic[TOPIC_LENGTH];
                        int sf;

                        sscanf(strchr(buffer, ' ') + 1, "%s %d", topic, &sf);

                        // Check if sf is valid
                        if (!(sf == 0 || sf == 1)) {
                            fprintf(stderr, "Invalid SF!\n");
                            continue;
                        }

                        int ret = send_subscribe_to_server(tcp_socket, topic, sf);
                        DIE(ret < 0, "send_subscribe_to_server");
                    } else if (strncmp(buffer, "unsubscribe", 11) == 0){
                        char topic[TOPIC_LENGTH];

                        sscanf(strchr(buffer, ' ') + 1, "%s", topic);
                        int ret = send_unsubscribe_to_server(tcp_socket, topic);
                        DIE(ret < 0, "send_unsubscribe_to_server");
                    } else {
                        fprintf(stderr, "Invalid input!\n");
                    }
                } else if (i == tcp_socket) {
                    // Message received from server
                    struct message m;
                    int ret = recv(i, &m, sizeof(m), 0);
                    DIE(ret < 0, "recv");

                    if(m.type == CLOSE_CLIENT) {
                        goto end;
                    }
                }
            }
        }
    }
end:
    close(tcp_socket);
    return 0;
}