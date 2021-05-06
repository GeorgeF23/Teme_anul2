#ifndef _LIST_H
#define _LIST_H 1

#include <stdlib.h>

typedef int (*cmp)(void *el1, void *el2);

typedef struct node *list;

/* Define a node in a generic list */
struct node {
    void *info;
    list next;
};

/**
 * @brief  Creates a new node for a list
 * @note   
 * @param  *el: the element stored in the node
 * @retval the newly created node / NULL on error
 */
struct node *create_node(void *el);

/**
 * @brief  Adds a new element to a list
 * @note   
 * @param  *l: pointer to the list
 * @param  *el: the new element
 * @retval 0 on error
 */
int insert(list *l, void *el);


#endif