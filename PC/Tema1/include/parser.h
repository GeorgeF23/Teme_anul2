#pragma once
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "skel.h"


#define MAX_RTABLE_ENTRIES 100000
#define MAX_RENTRY_SIZE 256



struct route_table_entry {
	__uint32_t prefix;
	__uint32_t next_hop;
	__uint32_t mask;
	int interface;
} __attribute__((packed));



struct Node {
	struct route_table_entry *value;
	struct Node *left;	// bit 0
	struct Node *right; // bit 1
};

/**
 * @brief  Creates a new node in the route table tree
 * @note   
 * @param  *route: the route entry that is stored in the node
 * @retval the newly created node
 */
struct Node *create_node(struct route_table_entry *route);

/**
 * @brief  Checks if a node is a leaf
 * @note   
 * @param  *node: the node that is being checked
 * @retval 1 if is leaf / 0 if is not leaf
 */
int is_leaf(struct Node *node);

/**
 * @brief  Adds a new entry to the route table tree
 * @note   
 * @param  *root: the root of the tree
 * @param  *value: the new entry
 * @retval None
 */
void insert(struct Node *root, struct route_table_entry *value);

/**
 * @brief  Calculates the mask length
 * @note   
 * @param  mask: the mask
 * @retval length of the mask
 */
int get_mask_length(__uint32_t mask);

/**
 * @brief  Get the value of nth bit
 * @note   MSB is 0, LSB is 31
 * @param  value: the source of the bit
 * @param  n: index
 * @retval the nth bit from value
 */
int get_bit(__uint32_t value, int n);

/**
 * @brief  Gets the best route from the route table tree
 * @note   
 * @param  *root: the root of the tree
 * @param  address: the address for whom the function searches the best route
 * @retval the best route
 */
struct route_table_entry *calculate_best_route(struct Node *root, __uint32_t address);

/**
 * @brief  Parses the routing table file
 * @note   
 * @param  *source_file: name of the file that contains the routing table
 * @param  *rtable: the destination where to put the routing table. Array of route_table_entry
 * @retval the number of entries parsed
 */
int read_rtable(char *source_file, struct Node *rtable);
