/*************************************************************************
* Author: MASnail
* Created Time: 2017年02月23日 星期四 20时08分56秒
* File Name: packup.cc
* Description: C++ file
************************************************************************/


/*
 * 原始套接字的设置
 *
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <netdb.h>

using namespace std;

//CRC校验和的计算
unsigned short checksum(unsigned short *addr, int len)
{
    register int nleft = len;
    register int sum = 0;
    register unsigned short *w = addr;
    short answer = 0;

    while(nleft > 1)
    {
	sum += *w++;
	nleft -= 2;
    }

    if(nleft == 1)
    {
	*(unsigned char*)(&answer) = *(unsigned char*)w;
	sum += answer;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer =~ sum;
    return answer;
}


void addhead(struct sockaddr_in *target, 
	unsigned short srcport,
	char *data)
{
    char buf[128] = { 0 };
    struct ip *ip;
    struct udphdr *tcp;
    int ip_len;

    //计算整个报文的长度
    ip_len = sizeof(struct ip) + sizeof(struct tcphdr) + strlen(data);

    //填充ip首部
    ip = (struct ip*)buf;
    ip->ip_v = IPVERSION;
    ip->ip_hl = sizeof(struct ip) >> 2;
    ip->ip_tos = 0;
    ip->ip_len = htons(ip_len);
    ip->ip_id = 0;
    ip->ip_off = 0;
    ip->ip_ttl = MAXTTL;
    ip->ip_p = IPPROTO_UDP;
    ip->ip_sum = 0;
    ip->ip_dst = target->sin_addr;
    ip->ip_src.s_addr = htonl(INADDR_ANY);//源地址


    //填充TCP首部
    tcp = (struct udphdr*)(buf + sizeof(struct ip));
    tcp->source = htons(srcport);
    tcp->dest = target->sin_port;
   // tcp->seq = random();
    tcp->len = htonl(ip_len - sizeof(struct ip));
   // tcp->doff = 5;
    //tcp->syn = 1;
    //memcpy(buf+sizeof(struct ip)+sizeof(struct udphdr), data)
    tcp->check = 0;//checksum((unsigned short*)tcp, sizeof(struct tcphdr));//计算校验和
}

int main(int argc,char *argv[])
{
    int skfd;
    struct sockaddr_in target;
    struct hostent *host;
    const int on = 1;
    unsigned short srcport;

    if(argc < 2)
    {
	printf("not have target ip\n");
	exit(0);
    }

    bzero(&target, sizeof(struct sockaddr_in));
    target.sin_family = AF_INET;
    target.sin_port = htons(8120);
    
    if(0 == inet_aton(argv[1], &target.sin_addr))
    {
	host = gethostbyname(argv[1]);
	if(host == NULL)
	{
	    printf("targe name erro\n");
	    exit(1);
	}
	//target.sin_addr = *(struct in_addr*)(host->h_addr_list[0]);
    }

    //协议字段设置为IPPROTO_TCP,创建原始的套接字
    if(0 > (skfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)))
    {
	perror("create error!");
        exit(1);
    }

    if(0 > setsockopt(skfd, IPPROTO_IP, IP_HDRINCL, &on,  sizeof(on)))
    {
	perror("ip_hdrincl failed!");
	exit(1);
    }

    srcport = 8121;
    char tmp[2];
    bzero(tmp, 0);
    tmp[0] = '2';

    
    addhead( &target, srcport, tmp);

    int index = 0;
    //while(index++ < 10)
    int ret = sendto(skfd, tmp, sizeof(char), 0, (struct sockaddr*)&target, sizeof(struct sockaddr)) ;
cout << skfd << endl;
cout << ret << endl;
    return 0;
}

