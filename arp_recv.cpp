#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>
#include <net/if.h>

void print_ethaddr(char*, unsigned char*);
int main(int argc, char* argv[]) {

    int arp_sock = socket(AF_PACKET, SOCK_DGRAM, htons(ETH_P_ARP));
    if(arp_sock < 0) {
        perror("Create arp sock");
        return 1;
    }
    /* ARPパケットを受信するIFをeth0に限定 */
    struct sockaddr_ll sockaddr;
    memset(&sockaddr, 0x0, sizeof(sockaddr));
    sockaddr.sll_family = AF_PACKET;
    sockaddr.sll_protocol = htons(ETH_P_ARP);
    sockaddr.sll_ifindex = if_nametoindex("eth0");
    if(bind(arp_sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        perror("Bind arp sock");
        return 1;
    }

    while(1) {
      char buf[256];
      memset(buf,0x0,sizeof(buf));
      int arp_size = recvfrom(arp_sock, buf, sizeof(buf), 0, NULL, NULL);
      if(arp_size < 0) {
         perror("Receive arp socket");
      }

      /* 受信したデータはARPパケットなので、その形にキャストして情報にアクセスする */
      struct ether_arp *arppack = (struct ether_arp*) buf;
      print_ethaddr("sender hardware address", arppack->arp_sha);
      print_ethaddr("target hardware address", arppack->arp_tha);
    }
    return 0;
}

void print_ethaddr(char* name, unsigned char* ethaddr) {
   printf("%s : %02x:%02x:%02x:%02x:%02x:%02x\n",name, ethaddr[0],ethaddr[1],ethaddr[2],ethaddr[3],ethaddr[4],ethaddr[5]);
}
