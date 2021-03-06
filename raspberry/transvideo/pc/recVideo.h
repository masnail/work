/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 09时16分40秒
* File Name: recVideo.h
* Description: HEAD File
*************************************************************************/

#ifndef RECVDEIO_H
#define RECVDEIO_H

#include "head.h"

#define _BUFF_CNT 10 //接受视频缓存帧数

class Recvideo
{
    private:
	char _port[6];//本地PORT
	int _endFlag = -1;//结束标志
	bool _vStart = false;//视频开始接受的判断

    private:
	struct sockaddr_in _sendip;//发送端地址
	socklen_t _addrlen;//长度

	int _fd;//文件描述符

    private:
	//缓冲区
	Mat _buff;

    private:
	int _row;//长
	int _col;//宽


    public:
	Recvideo();
	~Recvideo();

    public:
	void recVideo();//接受socket视频
	void changeSize();//改变图像尺寸
	void playVideo();//显示视频
	void recvStart();//视频接受开始的确认

};

#endif
