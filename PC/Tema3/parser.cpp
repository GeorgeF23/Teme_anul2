#include "include/parser.h"

using namespace std;
using json = nlohmann::json;

char *create_login_register_message(char *host, char type[]) {
    char *request = (char*)calloc(MAX_REQUEST_LENGTH, sizeof(char));
    char *line = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));

    if (!request || !line) return NULL;

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    cout << "username=";
    cin >> username;
    
    cout << "password=";
    cin >> password;

    json j;
    j["username"] = username;
    j["password"] = password;

    if (strcmp(type, "login") == 0) {
        sprintf(line, "POST /api/v1/tema/auth/login");
    } else {
        sprintf(line, "POST /api/v1/tema/auth/register");
    }

    compute_message(request, line);

    sprintf(line, "Host: %s", host);
    compute_message(request, line);

    sprintf(line, "Connection: keep-alive");
    compute_message(request, line);

    sprintf(line, "Content-Type: application/json");
    compute_message(request, line);

    sprintf(line, "Content-Length: %ld", strlen(j.dump().c_str()));
    compute_message(request, line);

    compute_message(request, "");
    compute_message(request, j.dump().c_str());

    free(line);
    return request;
}

char *create_request_message(char *host) {
    char command_type[MAX_COMMAND_LENGTH];
    cin >> command_type;

    if (strcmp(command_type, "exit") == 0) {
        // dynamically alloc exit message to match return value
        char *exit_message = (char *)calloc(5, sizeof(char));
        strcpy(exit_message, "exit");
        return exit_message;
    } else if (strcmp(command_type, "register") == 0) {
        return create_login_register_message(host, command_type);
    } else if (strcmp(command_type, "login") == 0) {
        return create_login_register_message(host, command_type);
    }

    return NULL;
}

int is_error(char *response) {
    char *code = strchr(response, ' ') + 1;
    if (code[0] != '2') return 1;
    return 0;
}

char *get_error_message(char *response) {
    return basic_extract_json_response(response);
}