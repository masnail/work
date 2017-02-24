/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 09时30分30秒
* File Name: recVideo.cc
* Description: C++ file
************************************************************************/
#include "recVideo.h"

Recvideo::Recvideo()
{
    //读取接收端的端口号
    FILE *fp = fopen("config","r");
    if(fp == NULL)
    {
	memcpy(_port, "8120", 4);
    }
    fread(_port, sizeof(char), sizeof(_port) - 1, fp);
    fclose(fp);

    //初始化socket
    _fd = socket_server_udp(atoi(_port));
    memset(&_sendip, 0, sizeof(struct sockaddr_in));
    
    _row = 200;
    _col = 200;
    _buff = Mat::zeros(_row, _col, CV_8UC3);
}

Recvideo::~Recvideo()
{
    close(_fd);
}

/* 接受视频
 *
 * @param buff 需要填充的缓冲区
 * @param index 填充缓冲区的下标
 *
 * 使用下标遍历方式
 */
void Recvideo::recVideo()
{

    int ret = 0,//接受返回值
    videoIndex = 0,//当前接受到帧的下标
    flag,//开始标志
    length = 0;//接受到数据的长度，减少发送和接受不匹配

    //开始接受数据
    recvStart();
    

    for(int i = 0; i < _row; ++i)
    {	
	//接受MAT的下标,UDP乱序
	ret = recvfrom(_fd, &videoIndex, sizeof(int), 0, NULL, NULL);
	if(-1 == ret)
	{
	    perror("recv Mat tmp_index data error!");
	    exit(-1);
	}
//	if(videoIndex > _row)
//	    return;

	uchar *pData = _buff.ptr<uchar>(videoIndex);

	//接受MAT数据
	length = 0;
	while(length < _col*3)
	{
	    ret = recvfrom(_fd, pData + length, _col*3 - length, 0, NULL, NULL);
	    if( _endFlag == ret)
	    {
		perror("recv Mat data error!");
		exit(-1);
	    }
	    length += ret;
	}
    } //for-end 
    imshow("recv", _buff);
    waitKey(30);

}

/* 改变图像尺寸 */
void Recvideo::changeSize()
{
    int ret;//接受返回值

    //接受Mat行
    ret = recvfrom(_fd, &_row, sizeof(int), 0, (struct sockaddr*)&_sendip, &_addrlen);
    if( -1 == ret)
    {
	perror("recv row data error!");
	exit(-1);
    }

    //接受Mat列
    ret = recvfrom(_fd, &_col, sizeof(int), 0, NULL, NULL);
    if( -1 == ret)
    {
	perror("recv col data error!");
	exit(-1);
    }
    //cout<<_row<<":"<<_col<<endl;
        
}

/* 显示视频 */
void Recvideo::playVideo()
{
  recVideo();
  imshow("recv",_buff);
  waitKey(20);
}
 
/* 视频接受开始确认 */
void Recvideo::recvStart()
{
    int ret,//接受返回值
	flag;//接受帧结束标志

    while(1)
    {
	//接受一帧的开始位置，减小图像错位
	ret = recvfrom(_fd, &flag, sizeof(int), 0, NULL, NULL);
	if( -1 == ret)
	{
	    cout << "recvfrom flag data error!" << endl;
	    exit(-1);
	}

	//接受一帧的开始位置,开始接受
	if(_endFlag == flag)
	{
	    break;
	   // _vStart = true;

	}	
    }
    //cout << flag << endl;
	//接收完毕，重新开始接受
	//_vStart = false;
}
