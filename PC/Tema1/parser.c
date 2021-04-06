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
    

    return 0;
}