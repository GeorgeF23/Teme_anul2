#include "parser.h"

int read_rtable(char *source_file, struct Node *rtable){
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

        struct route_table_entry *entry = malloc(sizeof(struct route_table_entry));
        DIE(entry == NULL, "read_rtable: malloc");

        entry->prefix = inet_addr(prefix);
        entry->next_hop = inet_addr(next_hop);
        entry->mask = inet_addr(mask);
        entry->interface = atoi(interface);

        insert(rtable, entry);

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

struct Node *create_node(struct route_table_entry *route){
	struct Node *new_node = malloc(sizeof(struct Node));
	new_node->value = route;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}

int is_leaf(struct Node *node){
    return (node->left == NULL) && (node->right == NULL);
}

int get_mask_length(__uint32_t mask){
    int length = 0;
    while(mask > 0){
        mask = mask >> 1;
        length++;
    }
    
    return length;
}

int get_bit(__uint32_t value, int n){
    return (value >> (31 - n)) & 1;
}

void insert(struct Node *root, struct route_table_entry *value){
    // int length = get_mask_length(value->mask);
    struct Node *p = root;

    int length = get_mask_length(value->mask);
    __uint32_t prefix = ntohl(value->prefix);
    
    for(int i = 0; i < length; i++){
        int bit = get_bit(prefix, i);
        if(bit == 0){
            if(p->left != NULL){
                p = p->left;
            } else {
                struct Node *temp = create_node(NULL);
                p->left = temp;
                p = temp;
            }
        } else {
            if(p->right != NULL){
                p = p->right;
            } else {
                struct Node *temp = create_node(NULL);
                p->right = temp;
                p = temp;
            }
        }
    }
    p->value = value;
}

struct route_table_entry *calculate_best_route(struct Node *root, __uint32_t address){
    struct Node *p = root;
    address = ntohl(address);
    
    for(int i = 0; ; i++){
        int bit = get_bit(address, i);
        if(bit == 1){
            if(p->right != NULL){
                p = p->right;
            } else {
                return p->value;
            }
        } else {
            if(p->left != NULL){
                p = p->left;
            } else {
                return p->value;
            }
        }
    }
    return NULL;
}