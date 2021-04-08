#include <queue.h>
#include "skel.h"
#include "parser.h"

struct arp_entry *get_arp_entry(__u32 ip, struct arp_entry *arptable, int arptable_size){
	for(int i = 0; i < arptable_size; i++){
		if(ip == arptable[i].ip){
			return &arptable[i];
		}
	}
    return NULL;
}

int main(int argc, char *argv[])
{
	packet m;
	int rc;

	struct Node *rtable = create_node(NULL);	// Initialize an empty tree for the routing table
	struct arp_entry *arptable = malloc(sizeof (struct arp_entry) * MAX_ARPTABLE_ENTRIES);

	int rtable_size = read_rtable(argv[1], rtable);	// Read the routing table file
	DIE(rtable_size == 0, "No routes found");

	int arptable_size = parse_arp_table(arptable);

	init(argc - 2, argv + 2);



	while (1) {
		rc = get_packet(&m);
		DIE(rc < 0, "get_message");
		
		// Extract headers from the packet
		struct ether_header *eth_hdr = (struct ether_header *)m.payload;
		struct iphdr *ip_hdr = (struct iphdr *)(m.payload + sizeof(struct ether_header));

		// Get the best route for the packet
		struct route_table_entry *best_route = calculate_best_route(rtable, ip_hdr->daddr);
		DIE(best_route == NULL, "no route found");
		
		// Update the eth_hdr to go through the best route
		memcpy(eth_hdr->ether_dhost, get_arp_entry(best_route->next_hop, arptable, arptable_size)->mac, ETH_ALEN);
		get_interface_mac(best_route->interface, eth_hdr->ether_shost);

		// Forward the packet
		send_packet(best_route->interface, &m);
	}
}
