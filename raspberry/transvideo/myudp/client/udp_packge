/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月23日 星期五 23时17分51秒
* File Name: udp_packge.cc
* Description: C++ file
************************************************************************/
#include <iostream>

unsigned long checksu(unsigned long * pData, int len)
{
	
}

void SetingUdp(
	IPHeadr *pIphdr,
	UDPHeadr *pUdphdr,
	char *data,
	int len
	)
{
    char buff[1024];
    char *ptr = buff;
    int sumLen = 0;
    unsigned long zero = 0;


    //源IP
    memcpy(ptr, &pIphdr->ipSource, sizeof(pIphdr->ipSource));
    ptr += sizeof(pIphdr->ipSource);
    sumLen += sizeof(pIphsr->ipSource);

    //目的IP
    memcpy(ptr, &pIphdr->ipDestination, sizeof(pIphdr->ipDestination));
    ptr += sizeof(pIphdr->ipDestination);
    sumLen += sizeof(pIphsr->ipDestination);

    //包含8位0
    memcpy(ptr, &zero, 1);
    ptr += 1；
    sumLen += 1;

    //协议
    memcpy(ptr, &pIphdr->ipProtocol, sizeof(pIphdr->ipProtocol));
    ptr += sizeof(pIphdr->ipProtocol);
    sumLen += sizeof(pIphsr->ipProtocol);

    //UDP长度
    memcpy(ptr, &pUdphdr->len, sizeof(pUdphdr->len));
    ptr += sizeof(pUdphdr->len);
    sumLen += sizeof(pUdphdr->len);

    //UDP源端口号
    memcpy(ptr, &pUdphdr->sourcePort, sizeof(pUdphdr->sourcePort));
    ptr += sizeof(pUdphdr->sourcePort);
    sumLen += sizeof(pUdphdr->sourcePort);

    //UDP目的端口号
    memcpy(ptr, &pUdphdr->destinationPort, sizeof(pUdphdr->destinationPort));
    ptr += sizeof(pUdphdr->destinationPort);
    sumLen += sizeof(pUdphdr->destinationPort);

    //UDP长度
    memcpy(ptr, &pUdphdr->len, sizeof(pUdphdr->len));
    ptr += sizeof(pUdphdr->len);
    sumLen += sizeof(pUdphdr->len);

    //16位的UDP校验和,置0
    memcpy(ptr, &zero, sizeof(zero));
    ptr += sizeof(zero);
    sumLen += sizeof(zero);

    //所载数据
    memcpy(ptr, data, len);
    ptr += len;
    sumLen += len;

    //最后的补齐
    for(int i = 0; i < len%2; ++i)
    {
	*ptr = 0;
	++ptr;
	++sumLen;
    }

    //计算校验和
    pUdphdr->checksum = CheckSum((unsigned long*)buff, sumLen);
}

int main(int argc, char *argv[])
{
    bool bIncl = true;
    
    setingUdp();
    sendto();
    return 0;
}
