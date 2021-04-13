#include "arp.h"

struct arp_table *init_arp_table(){
    struct arp_table *arp_table = malloc(sizeof(struct arp_table));
    DIE(arp_table == NULL, "init_arp_table malloc");

    arp_table->entries = malloc(sizeof(struct arp_entry) * MAX_ARPTABLE_ENTRIES);
    DIE(arp_table->entries == NULL, "init_arp_table malloc");

    arp_table->no_entries = 0;
    return arp_table;
}

void add_arp_entry(struct arp_table *arp_table, __u32 ip, uint8_t* mac){
    struct arp_entry new_entry;
    new_entry.ip = ip;
    memcpy(new_entry.mac, mac, ETH_ALEN);
    arp_table->entries[arp_table->no_entries++] = new_entry;
}

uint8_t *get_arp_entry(struct arp_table *arp_table, __u32 ip){
    for(int i = 0; i < arp_table->no_entries; i++){
        if(arp_table->entries[i].ip == ip){
            return arp_table->entries[i].mac;
        }
    }
    return NULL;
}