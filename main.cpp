#include <stdio.h>
#include "pcap.h"

int index = 0;
void print_raw_packet(const unsigned char* pkt_data, bpf_u_int32 caplen);
void print_ether_header(const unsigned char* pkt_data);
void print_ip_header(const unsigned char* pkt_data);
void print_tcp_header(const unsigned char* pkt_data);
void print_data(const unsigned char* pkt_data, bpf_u_int32 caplen);

//void build_ether_header(const unsigned char* mypkt_data, const unsigned char* pkt_data);
//void build_ip_header(const unsigned char* mypkt_data, const unsigned char* pkt_data);
//void build_tcp_header(const unsigned char* mypkt_data, const unsigned char* pkt_data);
//void build_pseudo_header(const unsigned char* mypkt_data, const unsigned char* pkt_data);
//unsigned short in_checksum(unsigned short* ptr, int nbytes);
//void build_data(const unsigned char* mypkt_data, const unsigned char* pkt_data);


struct pcap_pkhdr {  // defined in pcap.h
    struct timeval ts; // time stamp
    bpf_u_int32 caplen; // length of portion present
    bpf_u_int32 len; // length of this packet
};

struct ether_addr {
    unsigned char ether_addr_octet[6];
};

struct  ether_header {
    struct  ether_addr ether_dhost;
    struct  ether_addr ether_shost;
    unsigned short ether_type;          // 0x0800 for IP
};

struct  ether_header* myeh;   // create a etherhead structure

struct ip_hdr {
    unsigned char ip_header_len : 4;
    unsigned char ip_version : 4;
    unsigned char ip_tos;
    unsigned short ip_total_length;
    unsigned short ip_id;
    unsigned char ip_frag_offset : 5;
    unsigned char ip_more_fragment : 1;
    unsigned char ip_dont_fragment : 1;
    unsigned char ip_reserved_zero : 1;
    unsigned char ip_frag_offset1;
    unsigned char ip_ttl;
    unsigned char ip_protocol;
    unsigned short ip_checksum;
    unsigned int ip_srcaddr;
    unsigned int ip_destaddr;
};
struct tcp_hdr {
    unsigned short source_port;
    unsigned short dest_port;
    unsigned int sequence;
    unsigned int acknowledge;
    unsigned char ns : 1;
    unsigned char reserved_part1 : 3;
    unsigned char data_offset : 4;
    unsigned char fin : 1;
    unsigned char syn : 1;
    unsigned char rst : 1;
    unsigned char psh : 1;
    unsigned char ack : 1;
    unsigned char urg : 1;
    unsigned char ecn : 1;
    unsigned char cwr : 1;
    unsigned short window;
    unsigned short checksum;
    unsigned short urgent_pointer;
};

struct pseudo_header {
    unsigned int source_address;
    unsigned int dest_address;
    unsigned char placeholder;
    unsigned char protocol;
    unsigned short tcp_length;
};

void print_raw_packet(const unsigned char* pkt_data, bpf_u_int32 caplen) {
    puts("-------------RAW PACKET---------------");
    for (int i = 0; i < caplen; i++) {
        printf("%02x", pkt_data[i]);
        if (i % 2 == 1) printf(" ");
    }
    printf("\n\n");
}
void print_ether_header(const unsigned char* pkt_data) {
    puts("[Ethernet Header]");
    ether_header* eHeader = (ether_header*)pkt_data;

    //MAC addr : xx-xx-xx-xx-xx-xx
    printf("Src MAC Addr : ");
    for (int i = 0; i < 6; i++) {
        printf("%02x", eHeader->ether_shost.ether_addr_octet[i]);
        if (i != 5) printf("-");
    }puts("");
    printf("Dst MAC Addr : ");
    for (int i = 0; i < 6; i++) {
        printf("%02x", eHeader->ether_dhost.ether_addr_octet[i]);
        if (i != 5) printf("-");
    }puts("");

    // Ethernet type : xxxx
    printf("type : %04x", ntohs(eHeader->ether_type));
    puts("\n");

    // 14bytes
    index += 14;
}
//
//void build_ether_header(const unsigned char* mypkt_data, const unsigned char* pkt_data) {
//   struct ether_header* myeh = (struct ether_header*)mypkt_data;
//   struct ether_header* eh = (struct ether_header*)pkt_data;
//
//   for (int i = 0; i < 6; i++) {
//      myeh->ether_dhost.ether_addr_octet[i] = eh->ether_dhost.ether_addr_octet[i];
//      myeh->ether_shost.ether_addr_octet[i] = eh->ether_shost.ether_addr_octet[i];
//   }
//   myeh->ether_type = eh->ether_type;
//}

void print_ip_header(const unsigned char* pkt_data) {
    puts("[IP Header]");
    ip_hdr* IHeader = (ip_hdr*)(pkt_data + index);
    printf("ip_header_len : %01x\n", IHeader->ip_header_len);
    printf("ip_version : %01x\n", IHeader->ip_version);
    printf("ip_type of service : %02x\n", IHeader->ip_tos);
    printf("ip_total_length : %04x\n", IHeader->ip_total_length);
    printf("ip_id : %04x\n", IHeader->ip_id);
    printf("ip_more_fragment : %01x\n", IHeader->ip_more_fragment);
    printf("ip_dont_fragment : %01x\n", IHeader->ip_dont_fragment);
    printf("ip_frag_offset : %02x%02x\n", IHeader->ip_frag_offset, IHeader->ip_frag_offset1);
    printf("ip_ttl : %02x\n", IHeader->ip_ttl);
    printf("ip_protocol : %02x\n", IHeader->ip_protocol);
    printf("*****ip_checksum : %04x\n", IHeader->ip_checksum);
    printf("ip_srcaddr : %08x\n", IHeader->ip_srcaddr);
    printf("ip_destaddr : %08x\n", IHeader->ip_destaddr);
    index += IHeader->ip_header_len * 4;
    puts("\n");
}


unsigned short in_checksum(unsigned short* ptr, int nbytes) {
    register long sum;
    unsigned short oddbyte;
    register short answer;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char*)&oddbyte) = *(u_char*)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum = sum + (sum >> 16);
    answer = (SHORT)~sum;  // use ��short�� in MacOS

    return(answer);
}


void print_tcp_header(const unsigned char* pkt_data) {
    puts("[TCP Header]");
    tcp_hdr* THeader = (tcp_hdr*)(pkt_data + index);
    printf("source_port : %04x\n", THeader->source_port);
    printf("dest_port : %04x\n", THeader->dest_port);
    printf("sequence : %08x\n", THeader->sequence);
    printf("acknowledge : %08x\n", THeader->acknowledge);
    printf("data_offset : %01x\n", THeader->data_offset);
    // flags
    printf("urg : %01x\n", THeader->urg);
    printf("ack : %01x\n", THeader->ack);
    printf("psh : %01x\n", THeader->psh);
    printf("rst : %01x\n", THeader->rst);
    printf("syn : %01x\n", THeader->syn);
    printf("fin : %01x\n", THeader->fin);

    printf("window : %04x\n", THeader->window);
    printf("*****checksum : %04x\n", THeader->checksum);
    printf("urgent_pointer : %04x\n", THeader->urgent_pointer);
    index += THeader->data_offset * 4;
    puts("\n");
}


void print_data(const unsigned char* pkt_data, bpf_u_int32 caplen) {
    puts("[DATA]");
    for (int i = index; i < caplen; i++)
    {
        printf("%02x", pkt_data[i]);
        if (i % 2 == 1) printf(" ");
    }
    puts("");
}

int main() {
    pcap_if_t* alldevs = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    // find all network adapters
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        printf("dev find failed\n");
        return -1;
    }
    if (alldevs == NULL) {
        printf("no devs found\n");
        return -1;
    }
    // print them
    pcap_if_t* d; int i;
    for (d = alldevs, i = 0; d != NULL; d = d->next) {
        printf("%d-th dev: %s ", ++i, d->name);
        if (d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No description available)\n");
    }

    int inum;
    printf("enter the interface number: ");
    scanf_s("%d", &inum);
    for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++); // jump to the inum-th dev

    // open
    pcap_t* fp;
    if ((fp = pcap_open_live(d->name,      // name of the device
        65536,                   // capture size
        1,  // promiscuous mode
        20,                    // read timeout
        errbuf
    )) == NULL) {
        printf("pcap open failed\n");
        pcap_freealldevs(alldevs);
        return -1;
    }
    printf("pcap open successful\n");

    struct bpf_program  fcode;
    if (pcap_compile(fp,  // pcap handle
        &fcode,  // compiled rule
        (char*)("host 165.246.38.157 and port 2626"),  // filter rule
        1,            // optimize
        NULL) < 0) {
        printf("pcap compile failed\n");
        pcap_freealldevs(alldevs);
        return -1;
    }
    if (pcap_setfilter(fp, &fcode) < 0) {
        printf("pcap setfilter failed\n");
        pcap_freealldevs(alldevs);
        return -1;
    }
    printf("filter setting successful\n");

    pcap_freealldevs(alldevs); // we don't need this anymore
    struct pcap_pkthdr* header;
    const unsigned char* pkt_data;
    int res;
    int count = 0;
    unsigned char packet[65535];
    while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0) {// 1 if success
        index = 0;
        if (res == 0) continue; // 0 if time-out
        printf("[packet : %d] \n", count++);
        print_raw_packet(pkt_data, header->caplen);
        print_ether_header(pkt_data);
        print_ip_header(pkt_data);
        print_tcp_header(pkt_data);
        print_data(pkt_data, header->caplen);
    }

    
    return 0;
}




