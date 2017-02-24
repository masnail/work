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


void dpPacketSend(struct sockaddr_in *srcHost, struct sockaddr_in *destHost, char *udpData)
{
	int st;
	int ipLen;
	int udpDataLen;
	int pseLen;
	const int on = 1;
	char buf[128]={0}, *pse;
	struct ip *ipHeader;
	struct udphdr *udpHeader;

	if((st = socket(AF_INET, SOCK_RAW, IPPROTO_UDP))<0){
		perror("CREATE ERROR");
		exit(1);
	}

	if(setsockopt(st, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on))<0){
		perror("HDRINCL ERROR");
		exit(1);
	}

	setuid(getpid());
	udpDataLen = strlen(udpData);
	ipLen = sizeof(struct ip) + sizeof(struct udphdr) + udpDataLen;
	//IP首部参数修改
	ipHeader = (struct ip*)buf;
	ipHeader->ip_v = IPVERSION;
	ipHeader->ip_hl = sizeof(struct ip)>>2;
	ipHeader->ip_tos = 0;
	ipHeader->ip_len = htons(ipLen);
	ipHeader->ip_id = 0;
	ipHeader->ip_off = 0;
	ipHeader->ip_ttl = MAXTTL;
	ipHeader->ip_p = IPPROTO_UDP;
	ipHeader->ip_sum = 0;
	ipHeader->ip_dst = destHost->sin_addr;
	ipHeader->ip_src = srcHost->sin_addr;


	//UDP首部参数修改
	udpHeader = (struct udphdr*)(buf + sizeof(struct ip));
	udpHeader->source = srcHost->sin_port;
	udpHeader->dest=destHost->sin_port;
	udpHeader->len = htons(ipLen - sizeof(struct ip));
	udpHeader->check = 0;
	if(udpDataLen>0){
		memcpy(buf+sizeof(struct ip)+sizeof(struct udphdr),udpData,udpDataLen); 
	}
	
	//循环执行sento()可以控制数据包个数
	//
	cout << ipLen << endl;
	int ret = sendto(st,buf,ipLen,0,(struct sockaddr*)destHost,sizeof(struct sockaddr_in));
	close(st);
}

int main()
{
    struct sockaddr_in src,dst;
    bzero(&src, 0);
    bzero(&dst, 0);
    

    src.sin_family = AF_INET;
    src.sin_port = htons(8123);
    src.sin_addr.s_addr = inet_addr("127.0.0.1");

    dst.sin_family = AF_INET;
    dst.sin_port = htons(8120);
    dst.sin_addr.s_addr = inet_addr("127.0.0.1");

    cout << ntohs((src).sin_port) << endl;

    dpPacketSend(&src, &dst, "1666");
    return 0;
}
