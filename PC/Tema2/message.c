#include "message.h"

int subscription_has_topic(void *subscription, void *topic) {
    return strcmp(((struct subscription_info *)subscription)->topic, (char *)topic) == 0;
}
