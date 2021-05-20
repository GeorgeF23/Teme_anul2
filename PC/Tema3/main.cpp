#include <iostream>
#include "include/helpers.h"
#include "include/parser.h"

using namespace std;

int main() {
    char server_ip[] = "34.118.48.238";
    const int server_port = 8080;

    char last_command[MAX_COMMAND_LENGTH];
    char *cookie = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
    char *jwt = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));


    while(1) {
        // Generate the request
        char *request_message = create_request_message(server_ip, last_command, cookie, jwt);

        if (request_message == NULL) {
            continue;
        }

        if (strcmp(request_message, "exit") == 0) {
            free(request_message);
            break;
        }

        // Open the connection
        int sockfd = open_connection(server_ip, server_port, AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            free(request_message);
            free(cookie);
            free(jwt);
            error("Error while connecting to the server!\n");
        }
        
        // Send the request
        send_to_server(sockfd, request_message);

        // Receive the response
        char *response_message = receive_from_server(sockfd);

        // Check for errors
        if (is_error(response_message)) {
            cout << get_error_message(response_message) << "\n";
        } else {
            cout << last_command << " success!\n";

            if (strcmp(last_command, "login") == 0) {
                extract_cookie(response_message, cookie);
            } else if(strcmp(last_command, "enter_library") == 0) {
                extract_jwt(response_message, jwt);
            } else if(strcmp(last_command, "get_books") == 0) {
                cout << basic_extract_json_response(response_message) << "\n";
            } else if(strcmp(last_command, "get_book") == 0) {
                cout << basic_extract_json_response(response_message) << "\n";
            }
        }

        // Clear the memory, close the connection
        free(response_message);
        free(request_message);
        close_connection(sockfd);
    }
    free(cookie);
    free(jwt);
    return 0;
}