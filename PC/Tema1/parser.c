#include "parser.h"

int read_rtable(char *source_file, struct Node *rtable){
    FILE *fd = fopen(source_file, "r");
    DIE(fd == NULL, "read_rtable: open");

    char buffer[MAX_RENTRY_SIZE];

    int count = 0;


    while(fgets(buffer, MAX_RENTRY_SIZE, fd) != NULL)
    {
        // Split the string
        char *prefix = strtok(buffer, " \n");
        char *next_hop = strtok(NULL, " \n");
        char *mask = strtok(NULL, " \n"); 
        char *interface = strtok(NULL, " \n");

        struct route_table_entry *entry = malloc(sizeof(struct route_table_entry));
        DIE(entry == NULL, "read_rtable: malloc");

        // Put the information in the struct
        entry->prefix = inet_addr(prefix);
        entry->next_hop = inet_addr(next_hop);
        entry->mask = inet_addr(mask);
        entry->interface = atoi(interface);

        insert(rtable, entry);  // Put the entry into the tree

        memset(buffer, 0, MAX_RENTRY_SIZE); // Reset the buffer for the next entry
        count++;
    }
    
    fclose(fd);
    return count;
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
    struct Node *p = root;

    int length = get_mask_length(value->mask);
    __uint32_t prefix = ntohl(value->prefix);
    
    for(int i = 0; i < length; i++){    // Iterate through the bits of the prefix
        int bit = get_bit(prefix, i);
        if(bit == 0){   // If the bit is 0 we search in the left subtree
            if(p->left != NULL){    // If there is already a left child we keep on going
                p = p->left;
            } else {    // If there is no left child we make one
                struct Node *temp = create_node(NULL);
                p->left = temp;
                p = temp;
            }
        } else {    // If the bit is 1 we search in the right subtree
            if(p->right != NULL){   // If there is already a right child we keep on going
                p = p->right;
            } else {    // If there is no right child we make one
                struct Node *temp = create_node(NULL);
                p->right = temp;
                p = temp;
            }
        }
    }
    p->value = value;   // When we went through all the bits we put the entry in the node
}

struct route_table_entry *calculate_best_route(struct Node *root, __uint32_t address){
    struct Node *p = root;
    address = ntohl(address);
    

    for(int i = 0; ; i++){  // Iterate through the bits
        int bit = get_bit(address, i);
        if(bit == 1){   // If bit is 1 we go on the right subtree
            if(p->right != NULL){
                p = p->right;
            } else {    // If we cant go further that means we got our longest prefix match
                return p->value;
            }
        } else {       // If bit is 0 we go on the left subtree
            if(p->left != NULL){
                p = p->left;
            } else {    // If we cant go further that means we got our longest prefix match
                return p->value;
            }
        }
    }
    return NULL;
}