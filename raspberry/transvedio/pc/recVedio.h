/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 09时16分40秒
* File Name: recVedio.h
* Description: HEAD File
*************************************************************************/

#ifndef RECVDEIO_H
#define RECVDEIO_H

#include "head.h"

#define _BUFF_CNT 2 //接受视频缓存帧数

class Recvdeio
{
    private:
	int _port;//本地PORT
//	char _ip[17];//本地ip
	struct sockaddr_in _sendip;//发送端地址

	int _fd;//文件描述符
	Mat _vedio[_BUFF_CNT];//接受视频的一个帧

    public:
	Recvdeio(int port);
	~Recvdeio();
	void getVedio();//接受视频帧
	void transEnd();
	
	//图像的处理
};

#endif
