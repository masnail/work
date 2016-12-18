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

    Raspivideo raspi;
    
    while(1)
    {
	//raspi.readVideo();
	raspi.sendtoVideo();
//	waitKey(25);
    }

    return 0;
}

