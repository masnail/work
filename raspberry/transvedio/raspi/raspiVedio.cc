/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时18分37秒
* File Name: raspiVedio.cc
* Description: C++ file
************************************************************************/

#include "raspiVedio.h"

Raspivedio::Raspivedio(int port, char *ip)
    :_port(port)
{
    memset(_ip, 17, 0);
    memcpy(_ip, ip, 16);
    socket_client_udp(&_fd, _port, _ip, &_ipaddr);
}

Raspivedio::~Raspivedio()
{
    close(_fd);
}

void Raspivedio::readVedio()
{
   /* _vedio = imread("1.jpg");
    if(!_vedio.data)
    {	
	printf("read vedio NUll");
	return;
    }*/

    //摄像头采集
    VideoCapture capture(0);
    //waitKey(10);
  //  capture >> _vedio;
    //close(cap);
   // imshow("cap",_vedio);
    //cout<<_vedio.rows<<endl;
}

void Raspivedio::sendtoVedio(Mat _vedio)
{

    //获取Mat
    //readVedio();

    //获取vedio的大小
    int row = _vedio.rows,
	col = _vedio.cols;

    int ret = 0;

    //发送Mat行
    ret = sendto(_fd, &row, sizeof(int), 0, (struct sockaddr*)&_ipaddr, sizeof(struct sockaddr));
    if(-1 == ret)
    {
	perror("sendto row data error!");
	exit(-1);
    }

    //发送Mat列
    ret = sendto(_fd, &col, sizeof(int), 0, (struct sockaddr*)&_ipaddr, sizeof(struct sockaddr));
    if(-1 == ret)
    {
	perror("sendto col data error!");
	exit(-1);
    }

    //发送Mat
    int length = 0;
    for(int i = 0; i < row; ++i)
    {
	length =0;
	uchar *pData = _vedio.ptr<uchar>(i);
	while(length < col*3)
	{
	    ret = sendto(_fd, pData+length, col*3 - length, 0, (struct sockaddr*)&_ipaddr, sizeof(struct sockaddr));
	    if(-1 == ret)
	    {
		perror("sendto Mat data error!");
		exit(-1);
	    }
	    length += ret;
	}
    }
    
}
