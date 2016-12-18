/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月07日 星期四 19时22分01秒
 File Name: socket.h
 Description: 
 ************************************************************************/

#ifndef FUNC_HEAD_H
#define FUNC_HEAD_H


#include "head.h"

void socket_server_tcp(int*,int,/*char*,*/int);

void socket_accep(int,int*,struct sockaddr*);

void socket_client_tcp(int*,int,char*);

void socket_server_udp(int*,int);

void socket_client_udp(int*,int,char*, struct sockaddr_in*);

#endif
