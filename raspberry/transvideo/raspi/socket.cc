/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月08日 星期五 13时55分42秒
 File Name: socket.h
 Description: 
 ************************************************************************/

#include "socket.h"


void socket_server_tcp(int *fd_sock,int port,/*char *ipchar,*/int concnt)
{
	*fd_sock = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == *fd_sock)
	{
		perror("socket");
		exit(0);
	}

	int cancel_port=0;//cancel port res
	setsockopt(*fd_sock,SOL_SOCKET,SO_REUSEADDR,(const void*)&cancel_port,sizeof(int));

	struct sockaddr_in ip_addr;
	memset(&ip_addr,0,sizeof(ip_addr));
	ip_addr.sin_family=AF_INET;
	ip_addr.sin_port=htons(port);
	ip_addr.sin_addr.s_addr=/*inet_addr(ipchar);*/htonl(INADDR_ANY);

	int ret;
	ret = bind(*fd_sock,(struct sockaddr*)&ip_addr,sizeof(struct sockaddr));
	if(-1 == ret)
	{
		perror("bind");
		close(*fd_sock);
		exit(0);
	}
	
	ret = listen(*fd_sock,concnt);
	if(-1 == ret)
	{
		perror("listen");
		close(*fd_sock);
		exit(0);
	}
}

/*void socket_accept(int fd_sock,int *newfd,struct sockaddr *ip_addr)
{
	int addrlen = 0;
	if(!ip_addr)
		addrlen = sizeof(struct sockaddr);
	*newfd = accept(fd_sock,ip_addr,&addrlen);
	if(-1 == *newfd)
	{
		perror("accept");
		exit(0);
	}
}*/


void socket_client_tcp(int *fd_sock,int port,char *ipchar)
{
	*fd_sock = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == *fd_sock)
	{
		perror("socket");
		exit(0);
	}

	struct sockaddr_in ip_addr;
	memset(&ip_addr,0,sizeof(ip_addr));
	ip_addr.sin_family=AF_INET;
	ip_addr.sin_port=htons(port);
	ip_addr.sin_addr.s_addr=inet_addr(ipchar);
	
	int ret;
	ret = connect(*fd_sock,(struct sockaddr*)&ip_addr,sizeof(struct sockaddr));
	if(-1 == ret)
	{
		perror("connect");
		close(*fd_sock);
		exit(0);
	}
}


void socket_server_udp(int *fd_sock,int port)
{
	*fd_sock = socket(AF_INET,SOCK_DGRAM,0);
	if(-1 == *fd_sock)
	{
		perror("socket");
		exit(0);
	}
	struct sockaddr_in ip_addr;
	memset(&ip_addr,0,sizeof(ip_addr));
	ip_addr.sin_family=AF_INET;
	ip_addr.sin_port=htons(port);
	ip_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	int ret;
	ret = bind(*fd_sock,(struct sockaddr*)&ip_addr,sizeof(struct sockaddr));
	if(-1 == ret)
	{
		perror("bind");
		close(*fd_sock);
		exit(0);
	}	
}



void socket_client_udp(int *fd_sock,int port,char *ipchar,struct sockaddr_in *ip_addr)
{
	*fd_sock = socket(AF_INET,SOCK_DGRAM,0);
	if(-1 == *fd_sock)
	{
		perror("socket");
		exit(0);
	}

	memset(ip_addr,0,sizeof(struct sockaddr_in));
	(*ip_addr).sin_family=AF_INET;
	(*ip_addr).sin_port=htons(port);
	(*ip_addr).sin_addr.s_addr=inet_addr(ipchar);//INADDR_ANY;

}


