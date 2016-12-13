/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时18分22秒
* File Name: raspiVedio.h
* Description: HEAD File
*************************************************************************/

#ifndef RASPIVEDIO_H
#define RASPIVEDIO_H

#include "head.h"

class Raspivedio
{
    private:
	int _port;//接受端的PORT
	int _fd;//文件描述符
	char _ip[17];//接受端的ip
	
	struct sockaddr_in _ipaddr;//绑定后的族

	Mat _vedio;//摄像头的帧
	VideoCapture _cap;//摄像头的获取

    public:
	Raspivedio(int port, char *ip);
	~Raspivedio();
	//void readVedio();
	void sendtoVedio();
};

#endif
