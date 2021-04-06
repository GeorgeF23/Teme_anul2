#pragma once
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "skel.h"


#define MAX_RTABLE_ENTRIES 100000
#define MAX_RENTRY_SIZE 256

#define MAX_ARPTABLE_ENTRIES 100
#define MAX_ARPENTRY_SIZE 100

struct route_table_entry {
	__uint32_t prefix;
	__uint32_t next_hop;
	__uint32_t mask;
	int interface;
} __attribute__((packed));

struct arp_entry {
	__u32 ip;
	uint8_t mac[6];
};


/**
 * @brief  
 * @note   Parses the routing table file
 * @param  *source_file: name of the file that contains the routing table
 * @param  *rtable: the destination where to put the routing table. Array of route_table_entry
 * @retval the number of entries parsed
 */
int read_rtable(char *source_file, struct route_table_entry *rtable);

/**
 * @brief  
 * @note   Parses the arp_table.txt file
 * @param  *arp_table: destination of the arp table
 * @retval number of entries parsed
 */
int parse_arp_table(struct arp_entry *arp_table);