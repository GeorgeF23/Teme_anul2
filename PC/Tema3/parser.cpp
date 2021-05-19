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

    sprintf(line, "Content-Type: application/json");
    compute_message(request, line);

    sprintf(line, "Content-Length: %ld", strlen(j.dump().c_str()));
    compute_message(request, line);

    compute_message(request, "");
    compute_message(request, j.dump().c_str());

    free(line);
    return request;
}

char *create_access_request_message(char *host, char *cookie) {
    char *request = (char*)calloc(MAX_REQUEST_LENGTH, sizeof(char));
    char *line = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));

    sprintf(line, "GET /api/v1/tema/library/access");
    compute_message(request, line);

    sprintf(line, "Host: %s", host);
    compute_message(request, line);

    sprintf(line, "Cookie: %s", cookie);
    compute_message(request, line);

    compute_message(request, "");

    free(line);
    return request;
}

char *create_get_books_message(char *host, char *jwt) {
    char *request = (char*)calloc(MAX_REQUEST_LENGTH, sizeof(char));
    char *line = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));

    sprintf(line, "GET /api/v1/tema/library/books");
    compute_message(request, line);

    sprintf(line, "Host: %s", host);
    compute_message(request, line);

    sprintf(line, "Authorization: Bearer %s", jwt);
    compute_message(request, line);

    compute_message(request, "");

    free(line);
    return request;
}

char *create_get_book_message(char *host, char *jwt) {
    char *request = (char*)calloc(MAX_REQUEST_LENGTH, sizeof(char));
    char *line = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));

    int book_id;
    cout << "id=";
    cin >> book_id;

    sprintf(line, "GET /api/v1/tema/library/books/%d", book_id);
    compute_message(request, line);

    sprintf(line, "Host: %s", host);
    compute_message(request, line);

    sprintf(line, "Authorization: Bearer %s", jwt);
    compute_message(request, line);

    compute_message(request, "");

    free(line);
    return request;
}

char *create_add_book_message(char *host, char *jwt) {
    char *request = (char*)calloc(MAX_REQUEST_LENGTH, sizeof(char));
    char *line = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));

    string title, author, genre, publisher;
    int page_count;

    cout << "title=";
    cin >> title;
    cout << "author=";
    cin >> author;
    cout << "genre=";
    cin >> genre;
    cout << "publisher=";
    cin >> publisher;
    cout << "page_count=";
    cin >> page_count;

    json j;
    j["title"] = title;
    j["author"] = author;
    j["genre"] = genre;
    j["publisher"] = publisher;
    j["page_count"] = page_count;

    sprintf(line, "POST /api/v1/tema/library/books");
    compute_message(request, line);

    sprintf(line, "Host: %s", host);
    compute_message(request, line);

    sprintf(line, "Authorization: Bearer %s", jwt);
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

char *create_delete_book_message(char *host, char *jwt) {
    char *request = (char*)calloc(MAX_REQUEST_LENGTH, sizeof(char));
    char *line = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));

    int book_id;
    cout << "id=";
    cin >> book_id;

    sprintf(line, "DELETE /api/v1/tema/library/books/%d", book_id);
    compute_message(request, line);

    sprintf(line, "Host: %s", host);
    compute_message(request, line);

    sprintf(line, "Authorization: Bearer %s", jwt);
    compute_message(request, line);

    compute_message(request, "");

    free(line);
    return request;
}

char *create_logout_message(char *host, char *cookie) {
    char *request = (char*)calloc(MAX_REQUEST_LENGTH, sizeof(char));
    char *line = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));

    sprintf(line, "GET /api/v1/tema/auth/logout");
    compute_message(request, line);

    sprintf(line, "Host: %s", host);
    compute_message(request, line);

    sprintf(line, "Cookie: %s", cookie);
    compute_message(request, line);

    compute_message(request, "");

    free(line);
    return request;
}


char *create_request_message(char *host, char command[], char *cookie, char *jwt) {
    char command_type[MAX_COMMAND_LENGTH];
    cin >> command_type;

    strcpy(command, command_type);

    if (strcmp(command_type, "exit") == 0) {
        // dynamically alloc exit message to match return value
        char *exit_message = (char *)calloc(5, sizeof(char));
        strcpy(exit_message, "exit");
        return exit_message;
    } else if (strcmp(command_type, "register") == 0) {
        return create_login_register_message(host, command_type);
    } else if (strcmp(command_type, "login") == 0) {
        return create_login_register_message(host, command_type);
    } else if (strcmp(command_type, "enter_library") == 0) {
        return create_access_request_message(host, cookie);
    } else if (strcmp(command_type, "get_books") == 0) {
        return create_get_books_message(host, jwt);
    } else if (strcmp(command_type, "get_book") == 0) {
        return create_get_book_message(host, jwt);
    } else if (strcmp(command_type, "add_book") == 0) {
        return create_add_book_message(host, jwt);
    } else if (strcmp(command_type, "delete_book") == 0) {
        return create_delete_book_message(host, jwt);
    } else if (strcmp(command_type, "logout") == 0) {
        return create_logout_message(host, cookie);
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

void extract_cookie(char *response, char *cookie) {
    char *cookie_start = strstr(response, "Set-Cookie") + 12;
    char *cookie_end = strchr(cookie_start, '\r');

    strncpy(cookie, cookie_start, cookie_end - cookie_start);
}

void extract_jwt(char *response, char *jwt) {
    json j = json::parse(basic_extract_json_response(response));
    strcpy(jwt, j["token"].get<string>().c_str());
}