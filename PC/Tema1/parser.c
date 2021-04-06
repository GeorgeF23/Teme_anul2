#include "parser.h"

int read_rtable( char *source_file, struct route_table_entry *rtable){
    FILE *fd = fopen(source_file, "r");
    DIE(fd == NULL, "read_rtable: open");

    char buffer[MAX_RENTRY_SIZE];

    int count = 0;

    while(fgets(buffer, MAX_RENTRY_SIZE, fd) != NULL)
    {
        char *prefix = strtok(buffer, " \n");
        char *next_hop = strtok(NULL, " \n");
        char *mask = strtok(NULL, " \n"); 
        char *interface = strtok(NULL, " \n");

        rtable[count].prefix = inet_addr(prefix);
        rtable[count].next_hop = inet_addr(next_hop);
        rtable[count].mask = inet_addr(mask);
        rtable[count].interface = atoi(interface);

        memset(buffer, 0, MAX_RENTRY_SIZE);
        count++;
    }
    
    fclose(fd);
    return count;
}

int parse_arp_table(struct arp_entry *arp_table) 
{
    int arp_table_len;

	FILE *f = fopen("arp_table.txt", "r");
	DIE(f == NULL, "Failed to open arp_table.txt");
    
	char line[MAX_ARPENTRY_SIZE];
	int i = 0;
	for(i = 0; fgets(line, sizeof(line), f); i++) {
		char ip_str[MAX_ARPENTRY_SIZE / 2], mac_str[MAX_ARPENTRY_SIZE / 2];
		sscanf(line, "%s %s", ip_str, mac_str);
        
		arp_table[i].ip = inet_addr(ip_str);
		int rc = hwaddr_aton(mac_str, arp_table[i].mac);
		DIE(rc < 0, "invalid MAC");
	}
	arp_table_len = i;
	fclose(f);
    return arp_table_len;
}
