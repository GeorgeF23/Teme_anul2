#include "message.h"

int subscription_has_topic(void *subscription, void *topic) {
    return strncmp(((struct subscription_info *)subscription)->topic, (char *)topic, TOPIC_LENGTH) == 0;
}