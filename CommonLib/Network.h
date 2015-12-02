#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include<winsock2.h>
#include "Connection.h"
#include <map>
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
	bool server;
	Connection localConnection;
	std::map<std::string,Connection> connections;
	Connection *findConnection(std::string ip);
};

