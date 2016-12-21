/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时06分40秒
* File Name: main.cc
* Description: C++ file
************************************************************************/

#include "recVideo.h"
#include "Thread.h"

#include <iostream>
#include <pthread.h>

Recvideo recvideo;
void *playVideo(void *p)
{
    while(1)
    {
	cout << "playvideo" << endl;
	recvideo.playVideo();
    }
}

void *recvBuff(void *p)
{
    while(1)
    {
	cout << "recvbuff" << endl;
	recvideo.recvBuff();
    }
}

int main(int argc,char *argv[])
{
    Recvideo recvideo;
    Thread thread;
    cout << "start video" << endl;
    thread.playVideo(playVideo);
    thread.recvBuff(recvBuff);

    return 0;
}

