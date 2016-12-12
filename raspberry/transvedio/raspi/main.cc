/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时46分07秒
* File Name: main.cc
* Description: C++ file
************************************************************************/
#include <iostream>
#include <pthread.h>
#include "raspiVedio.h"
    
typedef struct ipaddr
{

    int port;
    char ip[17];
    char winame[5];
}ipaddr;

//子进程
void *pthread_fun(void *p)
{
    ipaddr *ip = (ipaddr*)p;

    Raspivedio raspi(ip->port, ip->ip);
    VideoCapture cap(ip->winame[0] - 65);
    Mat src;
    cap >> src;
   // src = imread("1.jpg");
    while(1)
    {
	cap >> src;
//	imshow(ip->winame,src);

	raspi.sendtoVedio(src);
	waitKey(50);
    }
    pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
    int port =8120;
    char ip[17] = "192.168.1.109";

    int cnt = 1;//线程数量

    ipaddr addr[2];
    for(int i = 0; i < cnt; ++i)
    {
	memset(&addr[i], sizeof(ipaddr), 0);
	addr[i].port = port + i;
	memcpy(addr[i].ip, ip, 16);
	addr[i].winame[0]=65 + i;
    }

    pthread_t pid[2];
    for(int i = 0; i < cnt; ++i)
    {
	pthread_create(&pid[i], NULL, pthread_fun, &addr[i]);
    }

    int ret = 0;
    while(ret != cnt)
    {
	for(int i = 0; i < cnt; ++i)
	{
	    if(pthread_join(pid[i], NULL) == 0);
		ret += 1;
	}
    }
    /*Raspivedio raspi(port, ip);
    VideoCapture cap(0);
    Mat src;
    while(1)
    {
	cap >> src;
	imshow("cap",src);

	raspi.sendtoVedio(src);
	waitKey(4);
    }*/

    return 0;
}

