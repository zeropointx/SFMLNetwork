#pragma once
#include <string>
#include<winsock2.h>
#define BUFLEN 512  //Max length of buffer
class Network
{
public:
	Network(std::string ip, unsigned short port, bool server);
	~Network();
	void Initialize();
private:
	void InitializeServer();
	void InitializeClient();
	void InitializeThreads();
	void ReceiveThread();
	void SendThread();
	std::string ip;
	unsigned int port;
	SOCKET socketThis;
	struct sockaddr_in socketAddrThis;
	bool server;
};

