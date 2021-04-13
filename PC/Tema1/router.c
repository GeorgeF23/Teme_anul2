#include <queue.h>
#include "skel.h"
#include "parser.h"
#include "arp.h"

/**
 * @brief  Stores the information necessary for the queued packets to be sent
 */
struct packet_queue_element {
	packet m;
	uint32_t next_hop_ip;
	int send_interface;
};

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

/**
 * @brief  Handles queued packets when an ARP reply is received
 * @note   
 * @param  packet_queue: the queue where the packets are stored
 * @param  next_hop_ip: the ip of the received arp entry
 * @param  *next_hop_mac: the mac of the received arp entry
 * @retval None
 */
void handle_queued_packets(queue packet_queue, uint32_t next_hop_ip, uint8_t *next_hop_mac){
	queue aux = queue_create();

	while(!queue_empty(packet_queue)){
		struct packet_queue_element *el = queue_deq(packet_queue);	// Extract packet from queue

		if(el->next_hop_ip == next_hop_ip){	// Check if his destination is the one that was just received in the ARP reply
			packet m = el->m;
			struct ether_header *eth_hdr = (struct ether_header *)m.payload;
			memcpy(eth_hdr->ether_dhost, next_hop_mac, ETH_ALEN);	// Place the destination MAC

			send_packet(el->send_interface, &m);	// Send the packet
		} else {	// Packets whose destination is not the one that was received in the ARP reply are put in an auxiliary queue
			queue_enq(aux, el);
		}
	}

	// The remaining packets are placed back in the queue
	while(!queue_empty(aux)){
		struct packet_queue_element *el = queue_deq(aux);
		queue_enq(packet_queue, el);
	}
}

int main(int argc, char *argv[])
{
	packet m;
	int rc;

	struct Node *rtable = create_node(NULL);	// Initialize an empty tree for the routing table
	struct arp_table *arp_table = init_arp_table();	// Initialize the arp table

	int rtable_size = read_rtable(argv[1], rtable);	// Read the routing table file
	DIE(rtable_size == 0, "No routes found");

	queue packet_queue = queue_create();


	init(argc - 2, argv + 2);



	while (1) {
		rc = get_packet(&m);
		DIE(rc < 0, "get_message");
		
		// Extract headers from the packet
		struct ether_header *eth_hdr = (struct ether_header *)m.payload;
		struct iphdr *ip_hdr = (struct iphdr *)(m.payload + sizeof(struct ether_header));

		struct arp_header* arp_hdr = parse_arp(&m.payload);

		if(arp_hdr != NULL) {	// Check if the packet is an ARP packet
			if(arp_hdr->op == htons(ARPOP_REQUEST)) {	// Check if is an ARP request
				int interface = is_router_ip(arp_hdr->tpa);
				if(interface != -1){	// Check if is router ip
					memcpy(eth_hdr->ether_dhost, arp_hdr->sha, ETH_ALEN);
					get_interface_mac(interface, eth_hdr->ether_shost);
					send_arp(arp_hdr->spa, arp_hdr->tpa, eth_hdr, interface, htons(ARPOP_REPLY));
				}
			}
			
			if(arp_hdr->op == htons(ARPOP_REPLY)) {	// Chek if is an ARP reply
				add_arp_entry(arp_table, arp_hdr->spa, arp_hdr->sha);	// Add the new entry

				handle_queued_packets(packet_queue, arp_hdr->spa, arp_hdr->sha);
			}
			continue;
		}

		if(eth_hdr->ether_type == htons(ETHERTYPE_IP)) { // Check if the packet is an IP packet

			if(ip_hdr->ttl == 1){	// If ttl is 1, then send back ICMP time exceeded error
				send_icmp_error(ip_hdr->saddr, inet_addr(get_interface_ip(m.interface)), eth_hdr->ether_dhost, eth_hdr->ether_shost, ICMP_TIME_EXCEEDED, 0, m.interface);
				continue;
			}


			// Check the checksum
			uint16_t received_iphdr_checksum = ip_hdr->check;
			ip_hdr->check = 0;
			uint16_t computed_iphdr_checksum = ip_checksum(ip_hdr, sizeof(struct iphdr));
			ip_hdr->check = computed_iphdr_checksum;

			if(received_iphdr_checksum != computed_iphdr_checksum) {
				continue;
			}

			if(ip_hdr->protocol == 1) {	// If packet is ICMP
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
			if(best_route == NULL) {	// If a route does not exist, send back error
				send_icmp_error(ip_hdr->saddr, inet_addr(get_interface_ip(m.interface)), eth_hdr->ether_dhost, eth_hdr->ether_shost, ICMP_DEST_UNREACH, ICMP_NET_UNREACH, m.interface);
				continue;
			}
			
			
			// Decrement ttl and update checksum before sending the packet
			ip_hdr->ttl--;
			ip_hdr->check = 0;
			ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

			// Update the eth_hdr to go through the best route
			get_interface_mac(best_route->interface, eth_hdr->ether_shost);
			uint8_t *next_hop_mac = get_arp_entry(arp_table, best_route->next_hop);

			if(next_hop_mac == NULL){ // Next hop is not in the arp table

				// Prepare an ARP request
				struct ether_header *arp_eth_hdr = malloc(sizeof(struct ether_header));
				get_interface_mac(best_route->interface, arp_eth_hdr->ether_shost);
				memset(arp_eth_hdr->ether_dhost, 0xFF, ETH_ALEN);
				arp_eth_hdr->ether_type = htons(ETHERTYPE_ARP);

				// Send the ARP request
				send_arp(best_route->next_hop, inet_addr(get_interface_ip(best_route->interface)), arp_eth_hdr, best_route->interface, htons(ARPOP_REQUEST));

				// Place the packet and aditional information in the queue
				struct packet_queue_element *queue_el = malloc(sizeof(struct packet_queue_element));
				queue_el->m = m;
				queue_el->next_hop_ip = best_route->next_hop;
				queue_el->send_interface = best_route->interface;

				queue_enq(packet_queue, queue_el);
				continue;
			}

			memcpy(eth_hdr->ether_dhost, next_hop_mac, ETH_ALEN); // If MAC is already known, put it in the header


			// Forward the packet
			send_packet(best_route->interface, &m);
		}
	}
}
