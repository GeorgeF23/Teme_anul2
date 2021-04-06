#include <queue.h>
#include "skel.h"
#include "parser.h"

int main(int argc, char *argv[])
{
	packet m;
	int rc;

	struct route_table_entry *rtable = malloc(sizeof (struct route_table_entry) * MAX_RTABLE_ENTRIES);
	struct arp_entry *arptable = malloc(sizeof (struct arp_entry) * MAX_ARPTABLE_ENTRIES);

	int rtable_size = read_rtable(argv[1], rtable);
	int arptable_size = parse_arp_table(arptable);

	init(argc - 2, argv + 2);

	while (1) {
		rc = get_packet(&m);
		DIE(rc < 0, "get_message");
		
		struct ether_header *eth_hdr = (struct ether_header *)m.payload;
		struct iphdr *ip_hdr = (struct iphdr *)(m.payload + sizeof(struct ether_header));


	}
}
