/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 09时30分30秒
* File Name: recVedio.cc
* Description: C++ file
************************************************************************/
#include "recVedio.h"

Recvdeio::Recvdeio(int port):
    _port(port)
{
    //memset(_ip, 17, 0);
    //memcpy(_ip, ip, 16);
    socket_server_udp(&_fd,port);//获取fd，绑定本机IP和PORT
    memset(&_sendip, 0, sizeof(struct sockaddr_in));
}

Recvdeio::~Recvdeio()
{
    close(_fd);
}

void Recvdeio::getVedio()
{
    int row,col;//Mat参数
    int ret = 0;
    char start_flag;
    int tmp_index = 0;//接受MAT的下标

    while(1)
    {
	//接受一帧的开始位置，减小图像错位
    	ret = recvfrom(_fd, &start_flag, sizeof(int), 0, NULL, NULL);
	if( -1 == ret)
	{
	    cout << "recvfrom flag data error!" << endl;
	    exit(-1);
	}

	//接受一帧的开始位置,开始接受
	if(-1 == start_flag)
	{
	    //cout << start_flag << endl;
	    break;
	}
    }

    //接受Mat行,地址长度固定，所以不必设置
    ret = recvfrom(_fd, &row, sizeof(int), 0, (struct sockaddr*)&_sendip, &_addrlen);
    if( -1 == ret)
    {
	perror("recv row data error!");
	exit(-1);
    }

    //接受Mat列
    ret = recvfrom(_fd, &col, sizeof(int), 0, NULL, NULL);
    if( -1 == ret)
    {
	perror("recv col data error!");
	exit(-1);
    }

    cout << row << " : " << col << endl;

    //初始化Mat 大小,以后不再分配地址
    if(!_vedio[0].data)
    {
	for(int i = 0; i < _BUFF_CNT; ++i)
	    _vedio[i] = Mat::zeros(row, col,  CV_8UC3);
    }

    int length = 0;
    int show_index = -1,storge_index = 0;//显示缓存视频帧,存储缓存视频帧
    
    //while(1)
    {
    for(int i = 0; i < row; ++i)
    {
	//按行接受
	//storge_index %= _BUFF_CNT;
	//uchar *pData = _vedio[storge_index++].ptr<uchar>(i);
	
	//接受MAT的下标
	ret = recvfrom(_fd, &tmp_index, sizeof(int), 0, NULL, NULL);
	if(-1 == ret /*|| tmp_index > row*/)
	{
	    perror("recv Mat tmp_index data error!");
	    exit(-1);
	}
	if(tmp_index > row)
	    return;

	//cout << tmp_index << endl;
	uchar *pData = _vedio[0].ptr<uchar>(tmp_index);

	//接受MAT数据
	length = 0;
	while(length < col*3)
	{
	    ret = recvfrom(_fd, pData + length, col*3 - length, 0, NULL, NULL);
	    if(-1 == ret)
	    {
		perror("recv Mat data error!");
		exit(-1);
	    }
	    length += ret;
	}

    }

   /* if(show_index++)
    {
	show_index %= _BUFF_CNT;
	imshow("rec",_vedio[show_index++]);
    }*/

    
    imshow("recv", _vedio[0]);
    waitKey(5) ;
    }
}

void Recvdeio::transEnd()
{
    
}
