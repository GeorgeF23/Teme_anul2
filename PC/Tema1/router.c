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

/**
 * @brief  Checks if an ip belongs to a router
 * @note   
 * @param  ip: the ip that is being checked
 * @retval the interface that has the ip / -1 if the ip does not belong to the router
 */
int is_router_ip(uint32_t ip){
	for(int i = 0; i < ROUTER_NUM_INTERFACES; i++){
		uint32_t router_ip = inet_addr(get_interface_ip(i));
		if(ip == router_ip){
			return i;
		}
	}
	return -1;
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

		if(eth_hdr->ether_type == htons(ETHERTYPE_IP)) { // Check if the packet is an IP packet

			if(ip_hdr->ttl == 1){
				send_icmp_error(ip_hdr->saddr, inet_addr(get_interface_ip(m.interface)), eth_hdr->ether_dhost, eth_hdr->ether_shost, ICMP_TIME_EXCEEDED, 0, m.interface);
				continue;
			}

			if(ip_hdr->protocol == 1) {	// ICMP packet
				struct icmphdr *icmp_hdr = parse_icmp(&m.payload);
				if(icmp_hdr->type == ICMP_ECHO){	// Check if the packet is ICMP Echo request
					int interface = is_router_ip(ip_hdr->daddr);
					if(interface != -1) {	// Check if the destination is an ip owned by the router
						send_icmp(ip_hdr->saddr, ip_hdr->daddr, eth_hdr->ether_dhost, eth_hdr->ether_shost, ICMP_ECHOREPLY, 0, interface, icmp_hdr->un.echo.id, icmp_hdr->un.echo.sequence);
						continue;
					}
				}
			}

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
}
