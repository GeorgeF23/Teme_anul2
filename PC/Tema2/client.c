#include "client.h"

int client_has_socket(void *client, void *socket) {
    return ((struct client_info *)client)->socket == *(int *)socket;
}

int client_has_id(void *client, void *id) {
    return strcmp(((struct client_info *)client)->id, (char *)id) == 0;
}

int client_subscribed_to(struct client_info *client, char *topic) {
    return search(client->subscriptions, topic, subscription_has_topic) != NULL;
}

int client_sf_to(struct client_info *client, char *topic) {
    if (client_subscribed_to(client, topic)) {
        return ((struct subscription_info *)search(client->subscriptions, topic, subscription_has_topic))->sf;
    }
    return -1;
}