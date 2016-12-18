/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时18分22秒
* File Name: raspiVideo.h
* Description: HEAD File
*************************************************************************/

#ifndef RASPIVEDIO_H
#define RASPIVEDIO_H

#include "head.h"

class Raspivideo
{
    private:
	char _port[6];//接受端的PORT
	int _fd;//文件描述符
	char _ip[17];//接受端的ip
	int start_flag;// '#' 视频开始的标志
	
	struct sockaddr_in _ipaddr;//绑定后的族
	
	Mat _video;//摄像头的帧
	raspicam::RaspiCam_Cv _camera;//摄像头的获取
	VideoCapture _cap;

	FILE *_fp;//配置文件描述符

    public:
	Raspivideo();
	~Raspivideo();
	void readVideo();
	void sendtoVideo();
};

#endif
