/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时06分40秒
* File Name: main.cc
* Description: C++ file
************************************************************************/

#include "recVedio.h"
#include <iostream>
#include <pthread.h>

typedef struct ipaddr
{
    int port;
    char winame[5];
}ipaddr;

void  *pthread_fun(void *p)
{
    ipaddr *ip = (ipaddr*)p;
    Recvdeio vedio(ip->port);

    cout << ip->winame << endl;
//	imshow(ip->winame,vedio.getVedio());
    //while(1)
    {
	//cout<<"1"<<endl;
	vedio.getVedio();
	//imshow(ip->winame,vedio.getVedio());
	//waitKey(40);
    }
}

int main(int argc,char *argv[])
{
    int port = 8120;
    char ip[17] = "192.168.109";
    int cnt = 1;//线程的数量

    ipaddr addr[2];
    for(int i = 0; i < cnt; ++i)
    {
	memset(&addr[i], sizeof(ipaddr), 0);
	addr[i].port = port + i;
	addr[i].winame[0] = 70 + i;
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
	    if(pthread_join(pid[i], NULL) == 0)
		ret += 1;
	}
    }

   // Recvdeio vedio(port);
    
    //while(1)
    //imshow("recv", vedio.getVedio());

   // Recvdeio vedio1(8119);
   // imshow("recv2",vedio1.getVedio());
    
    return 0;
}

