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
    strncpy(command.un.sub_info.topic, topic, TOPIC_LENGTH);
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
    strncpy(command.un.sub_info.topic, topic, TOPIC_LENGTH);

    // Send the command
    int ret = send(socket, &command, sizeof(command), 0);
    if (ret < 0) return -1;
    return 0;
}

void print_message(struct message_info msg_info) {
    char topic_buffer[TOPIC_LENGTH + 1];
    memcpy(topic_buffer, msg_info.msg.topic, TOPIC_LENGTH);
    topic_buffer[TOPIC_LENGTH] = '\0';
    printf("%s:%d - %s - ", msg_info.source_ip, msg_info.source_port, topic_buffer);
    
    if (msg_info.msg.type == INT_TYPE) {
        printf("INT - ");

        if (msg_info.msg.contents.int_info.sign == 1) {
            printf("-");
        }

        printf("%d\n", ntohl(msg_info.msg.contents.int_info.value));
    } else if (msg_info.msg.type == SHORT_REAL_TYPE) {
        printf("SHORT_REAL - ");
        float value = ((float)ntohs(msg_info.msg.contents.short_real_info.value)) / 100;
        if (value == floorf(value)) {
            // The number does not have decimal points
            printf ("%d\n", (int)value);
        } else {
            printf("%.2f\n", value);
        }
    } else if (msg_info.msg.type == FLOAT_TYPE) {
        printf("FLOAT - ");

        if (msg_info.msg.contents.int_info.sign == 1) {
            printf("-");
        }
        float value = ((float)ntohl(msg_info.msg.contents.float_info.value)) / pow(10, msg_info.msg.contents.float_info.decimal_digits);
        if (value == floorf(value)) {
            // The number does not have decimal points
            printf ("%d\n", (int)value);
        } else {
            printf("%.*f\n", msg_info.msg.contents.float_info.decimal_digits, value);
        }
    } else {
        char buffer[CONTENT_LENGTH + 1];
        memcpy(buffer, msg_info.msg.contents.string_info.value, CONTENT_LENGTH);
        buffer[CONTENT_LENGTH] = '\0';
        printf("STRING - %s\n", buffer);
    }
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
                    DIE(fgets(buffer, sizeof(buffer), stdin) == NULL, "fgets");

                    if (strncmp(buffer, "exit", 4) == 0) {
                        // Tell the server to close the socket
                        struct client_command_info command;
                        command.type = EXIT;

                        int ret = send(tcp_socket, &command, sizeof(command), 0);
                        DIE(ret < 0, "send");
                        goto end;
                    } else if (strncmp(buffer, "subscribe", 9) == 0){
                        char topic[TOPIC_LENGTH + 1];
                        int sf;

                        sscanf(strchr(buffer, ' ') + 1, "%s %d", topic, &sf);

                        // Check if sf is valid
                        if (!(sf == 0 || sf == 1)) {
                            fprintf(stderr, "Invalid SF!\n");
                            continue;
                        }

                        int ret = send_subscribe_to_server(tcp_socket, topic, sf);
                        DIE(ret < 0, "send_subscribe_to_server");

                        printf("Subscribed to topic.\n");
                    } else if (strncmp(buffer, "unsubscribe", 11) == 0){
                        char topic[TOPIC_LENGTH + 1];

                        sscanf(strchr(buffer, ' ') + 1, "%s", topic);
                        int ret = send_unsubscribe_to_server(tcp_socket, topic);
                        DIE(ret < 0, "send_unsubscribe_to_server");

                        printf("Unsubscribed from topic.\n");
                    } else {
                        fprintf(stderr, "Invalid input!\n");
                    }
                } else if (i == tcp_socket) {
                    // Message received from server
                    struct message_info msg_info;
                    int ret = recv(i, &msg_info, sizeof(msg_info), 0);
                    DIE(ret < 0, "recv");

                    if(msg_info.msg.type == CLOSE_CLIENT) {
                        goto end;
                    } else {
                        print_message(msg_info);
                    }
                }
            }
        }
    }
end:
    close(tcp_socket);
    return 0;
}