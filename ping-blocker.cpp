#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;

int main(int argc, char **argv) {
    int sockfd;
    char buffer[4096];
    struct sockaddr_in addr;
    struct icmp *icmp_header;
    struct sockaddr_in from_addr;
    socklen_t from_addr_len;
    int len, n;

    if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
        perror("socket");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return -1;
    }

    while(true) {
        from_addr_len = sizeof(from_addr);
        if((n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&from_addr, &from_addr_len)) < 0) {
            perror("recvfrom");
            return -1;
        }

        icmp_header = (struct icmp*)buffer;
        if(icmp_header->icmp_type == ICMP_ECHO) {
            cout << "Blocked ICMP Echo from " << inet_ntoa(from_addr.sin_addr) << endl;
            continue;
        }

        if((len = sendto(sockfd, buffer, n, 0, (struct sockaddr*)&from_addr, sizeof(from_addr))) < 0) {
            perror("sendto");
            return -1;
        }
    }

    return 0;
}
