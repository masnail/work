/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时46分07秒
* File Name: main.cc
* Description: C++ file
************************************************************************/
#include <iostream>
#include <pthread.h>
#include "raspiVideo.h"
    
int main(int argc,char *argv[])
{
    int port =8120;
    char ip[17] = "192.168.1.115";


    Raspivideo raspi(port, ip);
    
    while(1)
    {
	//raspi.readVideo();
	raspi.sendtoVideo();
	waitKey(30);
    }

    return 0;
}

