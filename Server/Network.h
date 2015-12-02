#pragma once
#define BUFLEN 512  //Max length of buffer
#include<winsock2.h>
class Network
{
public:
	Network(unsigned int port);
	~Network();
private:
	char buf[BUFLEN];
	int port;
	void ReceiveThread();
	void SendThread();
	SOCKET serverSocket;
};

