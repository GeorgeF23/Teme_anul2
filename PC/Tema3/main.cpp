#include <iostream>
#include "include/nlohmann/json.hpp"
#include "include/helpers.h"


using namespace std;
using json = nlohmann::json;

int main() {
    char server_ip[] = "34.118.48.238";
    const int server_port = 8080;

    int sockfd = open_connection(server_ip, server_port, AF_INET, SOCK_STREAM, 0);

    close_connection(sockfd);
}