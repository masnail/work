#########################################################################
# Author: MASnail
# Created Time: 2016年12月13日 星期二 23时55分30秒
# File Name: uv4l.sh
# Description: SH File
#########################################################################
#!/bin/bash
#apt-get update
#apt-get upgrade

#curl http://www.linux-projects.org/listing/uv4l_repo/lrkey.asc | sudo apt-key add -
#echo "deb http://www.linux-projects.org/listing/uv4l_repo/raspbian/ wheezy main" >> etc/apt/sources.list


#apt-get install uv4l uv4l-raspicam
service uv4l_raspicam restart
apt-get install uv4l-server
apt-get install uv4l-uvc
apt-get install uv4l-xscreen
apt-get install uv4l-mjpegstream
uv4l --driver raspicam --auto-video_nr --width 640 --height 480 --encoding mjpeg

