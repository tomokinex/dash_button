#include "defines.hpp"

int main(int argc, char* argv[]) {
    /*ソケットを作成*/
    int arp_sock = socket(AF_PACKET, SOCK_DGRAM, htons(ETH_P_ARP));
    if(arp_sock < 0) {
        perror("Create arp sock");
        return 1;
    }

    /*ARPのソケットをbind*/
    struct sockaddr_ll sockaddr;
    memset(&sockaddr, 0x0, sizeof(sockaddr));
    sockaddr.sll_family = AF_PACKET;
    sockaddr.sll_protocol = htons(ETH_P_ARP);
    sockaddr.sll_ifindex = if_nametoindex("eth0");
    if(bind(arp_sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        perror("Bind arp sock");
        return 1;
    }

    /*Dash buttonのMACアドレスを格納*/
    unsigned char button_addr[6];
    read_button_address(button_addr);
     if(daemon(0, 0) == 0) {
         main_loop(arp_sock, button_addr);
     }else{
         perror("Make demon process");
         return 1;
     }
     return 0;
}
void main_loop(int arp_sock, unsigned char* button_addr){
    
    /*受信*/
    while(1) {
      char buf[256];
      memset(buf,0x0,sizeof(buf));
      int arp_size = recvfrom(arp_sock, buf, sizeof(buf), 0, NULL, NULL);
      if(arp_size < 0) {
         perror("Receive arp socket");
      }

      /*受信したデータをARPパケットにキャスト*/
      struct ether_arp *arppack = (struct ether_arp*) buf;
      if(addr_matching(button_addr,arppack->arp_sha)){
          //cout << "match !" << endl;
          execute();
      }
    }
    return;
}


