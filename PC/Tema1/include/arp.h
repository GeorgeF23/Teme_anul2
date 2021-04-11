#pragma once
#include "skel.h"

#define MAX_ARPTABLE_ENTRIES 100
#define MAX_ARPENTRY_SIZE 100

struct arp_table {
    struct arp_entry *entries;
    size_t no_entries;
};

struct arp_entry {
	__u32 ip;
	uint8_t mac[6];
};


/**
 * @brief  Initializes the arp table
 * @note   
 * @retval pointer to the arp table
 */
struct arp_table *init_arp_table();

/**
 * @brief  Add a new entry to the arp table
 */
void add_arp_entry(struct arp_table *arp_table, __u32 ip, uint8_t* mac);

/**
 * @brief  Search the arp table for the mac address found at an ip
 * @note   
 * @param  *arp_table: the arp table
 * @param  ip: the ip whom MAC address we want to get
 * @retval pointer to the MAC address or NULL if not found 
 */
uint8_t *get_arp_entry(struct arp_table *arp_table, __u32 ip);