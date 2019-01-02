#include <stdio.h>
#include <iostream>
#include <fstream>
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
using namespace std;
void read_button_address(unsigned char* button_addr){
    ifstream ifs("./address.txt");
    if(ifs.fail()){
        perror("Open address.txt");
        return;
    }
    char str[256];
    if(!ifs.getline(str, 255)){
        perror("Read address.txt");
        return;
    }
    for(int i=0;i<=5;++i){
        str[(i+1)*3-1] = '\0';
        button_addr[i] = strtol(str+i*3,NULL,16);
    }
}

bool addr_matching(unsigned char* addr1, unsigned char* addr2){
    return addr1[0] == addr2[0] && addr1[1] == addr2[1] && addr1[2] == addr2[2] && addr1[3] == addr2[3] && addr1[4] == addr2[4] && addr1[5] == addr2[5];
}

void execute();