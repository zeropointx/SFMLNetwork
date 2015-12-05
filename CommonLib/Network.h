#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include<winsock2.h>
#include "Connection.h"
#include <map>
#include "Packet.h"
#define BUFLEN 512  //Max length of buffer
class Network
{
	struct PacketData
	{ 
		Packet *packet;
		Connection *connection;
	 };
public:
	Network(std::string ip, unsigned short port, bool server);
	~Network();
	void Initialize();
	void Send(Packet *data,Connection *sendTo);
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
	std::vector<PacketData> outData;
	std::vector<PacketData> inData;

	Connection *findConnection(std::string ip,std::string port);
};

