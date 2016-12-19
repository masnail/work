/*************************************************************************
* Author: MASnail
* Created Time: 2016年12月12日 星期一 10时18分37秒
* File Name: raspiVideo.cc
* Description: C++ file
************************************************************************/

#include "raspiVideo.h"

Raspivideo::Raspivideo()
{
    memset(_ip, 17, 0);

    //读取配置文件，减少编译时间
    _fp = fopen("config","r");
    if(_fp == NULL)
    {
	perror("read config file error!");
	exit(-1);
    }
    fgets(_ip, 16, _fp);
    fgets(_port, 5, _fp);
    fclose(_fp);//关闭文件


    //视频开始标志赋值
    start_flag = -1;
    //adp socket 建立
    socket_client_udp(&_fd, atoi(_port), _ip, &_ipaddr);
    _cap.open(0);//打开摄像头
/*    _camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    if(!_camera.open())
    {
	cout << "open camera fail" << endl;
	exit(-1);
    }*/
}

Raspivideo::~Raspivideo()
{
    close(_fd);//关闭scoket
    _camera.release();//释放摄像头
}

void Raspivideo::readVideo()
{
    //摄像头采集
  _cap >> _video;
  //sendtoVideo();
    
    /* raspi video */
   // _camera.grab();
   // _camera.retrieve(_video);

}

void Raspivideo::sendtoVideo()
{  

    //摄像头采集
    readVideo();

    if(!_video.data)
    {
	cout << "capture video error!" << endl;
	return;
    }
    //cvtColor(_video, _video, COLOR_HLS2RGB);
    resize(_video, _video, Size(500, 600));

    //获取video的大小
    int row = _video.rows,
	col = _video.cols;

    int ret = 0;

    //发送视频开始标志 #
    ret = sendto(_fd, &start_flag, sizeof(int), 0, (struct sockaddr*)&_ipaddr, sizeof(struct sockaddr));
    if(-1 == ret)
    {
	perror("sendto start_flag data error!");
	exit(-1);
    }

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
	int tmp = i;
	//发送mat的开始索引，解决UDP无序问题
	ret = sendto(_fd, &tmp, sizeof(int), 0, (struct sockaddr*)&_ipaddr, sizeof(struct sockaddr));
	if(-1 == ret)
	{
	    perror("sendto Mat row index error!");
	    exit(-1);
	}

	length =0;
	uchar *pData = _video.ptr<uchar>(i);
	while(length < col*3)
	{
	    length += ret;

	    //发送MAT一行的数据
	    ret = sendto(_fd, pData+length, col*3 - length, 0, (struct sockaddr*)&_ipaddr, sizeof(struct sockaddr));
	    if(-1 == ret)
	    {
		perror("sendto Mat data error!");
		exit(-1);
	    }
	    length += ret;
	}
    }

   	    
    // imshow("raspi",_video);
    // imwrite("2.jpg",_video);
    
}
