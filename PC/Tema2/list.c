#include "list.h"

struct node *create_node(void *el) {
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) return NULL;
    
    new_node->info = el;
    new_node->next = NULL;
    return new_node;
}

int insert(list *l, void *el) {
    if (*l == NULL) {
        *l = create_node(el);
        if (*l == NULL) return 0;
        return 1;
    }

    list p;
    for (p = *l; p->next != NULL; p = p->next);
    
    p->next = create_node(el);
    if (p->next == NULL) return 0;
    return 1;
}