/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月07日 星期四 19时22分01秒
 File Name: socket.h
 Description: 
 ************************************************************************/

#ifndef FUNC_HEAD_H
#define FUNC_HEAD_H


#include <sys/types.h>
#include <sys/socket.h>


int socket_server_tcp(int,/*char*,*/int);

int socket_client_tcp(int,char*);

int socket_server_udp(int);

int socket_client_udp(int,char*, struct sockaddr_in*);

#endif
