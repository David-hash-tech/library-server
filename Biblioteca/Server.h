#pragma once
#include <winsock.h>

#pragma comment (lib, "Ws2_32.lib")
#define MaxClienti 5
#define PORT 1456

class Server
{
private:
	WSADATA wsa;
	int nSocket;
	int maxFd;
	static int ClientSocket[];
	struct sockaddr_in srv;

	fd_set fr, fw, fe;	//socket descriptors
						//nr si un vector de max 64 sockets
	// fr - colectia de socket descriptori pe care le citesc
	// fw - colectia de socket descriptori pe care sunt gata sa le scriu
	// fe - colectia de socket descriptori cu exceptii 

	int RetValue;
	int nOptVal = 0;

	void ProcessNewRequest();
	void ProcessNewMsg(int Socket);

	void wsaInit();
	void SocketInit();
	void SockaddrInit();
	void SocketOptions();
	void Bind();
	void Listen();

public:
	void startServer();
};

