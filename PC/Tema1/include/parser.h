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

/**
 * @brief  
 * @note   Parses the routing table file
 * @param  *source_file: name of the file that contains the routing table
 * @param  *rtable: the destination where to put the routing table. Array of route_table_entry
 * @retval the number of entries parsed
 */
int read_rtable(char *source_file, struct route_table_entry *rtable);
