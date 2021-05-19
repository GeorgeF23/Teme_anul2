#include <iostream>
#include "include/helpers.h"
#include "include/parser.h"

using namespace std;

int main() {
    char server_ip[] = "34.118.48.238";
    const int server_port = 8080;


    while(1) {
        // Generate the request
        char *request_message = create_request_message(server_ip);

        if (request_message == NULL) {
            fprintf(stderr, "Invalid command!\n");
            continue;
        }

        if (strcmp(request_message, "exit") == 0) {
            free(request_message);
            break;
        }

        // Open the connection
        int sockfd = open_connection(server_ip, server_port, AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            error("Error while connecting to the server!\n");
        }
        
        // Send the request
        send_to_server(sockfd, request_message);

        // Receive the response
        char *response_message = receive_from_server(sockfd);

        cout << response_message;

        // Clear the memory, close the connection
        free(response_message);
        free(request_message);
        close_connection(sockfd);
    }
    return 0;
}