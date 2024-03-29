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

void *search(list l, void *other, equals eq) {
    for (list p = l; p != NULL; p = p->next) {
        if (eq(p->info, other) == 1) {
            return p->info;
        }
    }
    return NULL;
}

void remove_node(list *l, void *info) {
    if ((*l)->info == info) {
        // First element in list matches
        *l = (*l)->next;
    } else {
        list ant = (*l);
        for (list p = (*l)->next; p != NULL; p = p->next) {
            if (p->info == info) {
                ant->next = p->next;
            }
            ant = p;
        }
    }
}

void free_list(list l) {
    if (l == NULL) return;
    
    list aux = l->next;
    free(l);
    free_list(aux);
}