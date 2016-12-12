/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时46分07秒
* File Name: main.cc
* Description: C++ file
************************************************************************/
#include <iostream>
#include <pthread.h>
#include "raspiVedio.h"
    
int main(int argc,char *argv[])
{
    int port =8120;
    char ip[17] = "192.168.1.109";


    Raspivedio raspi(port, ip);
    VideoCapture cap(0);
    Mat src;
    while(1)
    {
	cap >> src;
	//imshow("cap",src);

	raspi.sendtoVedio(src);
	waitKey(30);
    }

    return 0;
}

