/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时06分40秒
* File Name: main.cc
* Description: C++ file
************************************************************************/

#include "recVideo.h"

#include <iostream>

int main(int argc,char *argv[])
{
    Recvideo recvideo;
    while(1)
    {
	recvideo.recVideo();
    }
    
/*    pthread_t pth[2];

    pthread_create(&pth[0], NULL, recvBuff, &recvideo);
    pthread_create(&pth[1], NULL, playVideo, &recvideo);

    pthread_join(pth[0],NULL);
    pthread_join(pth[1],NULL);*/

    return 0;
}

