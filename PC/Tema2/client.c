#include "client.h"

int client_has_socket(void *client, void *socket) {
    return ((struct client_info *)client)->socket == *(int *)socket;
}

int client_has_id(void *client, void *id) {
    return strcmp(((struct client_info *)client)->id, (char *)id) == 0;
}