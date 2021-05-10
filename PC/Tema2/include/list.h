#ifndef _LIST_H
#define _LIST_H 1

#include <stdlib.h>

typedef int (*equals)(void *el1, void *el2);

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

/**
 * @brief  Search for an element in list
 * @note   
 * @param  l: the list
 * @param *other: the element we search for
 * @param  eq: equals function. Returns 1 if is a match / 0 if not
 * @retval Info field in the node
 */
void *search(list l, void *other, equals eq);

/**
 * @brief  Removes a node from a list
 * @note   
 * @param  *l: the list
 * @param  *info: the info field of the node
 * @retval None
 */
void remove_node(list *l, void *info);

/**
 * @brief  Frees the memory allocated for a list
 * @note   
 * @param  *l: the list
 * @retval None
 */
void free_list(list l);
#endif