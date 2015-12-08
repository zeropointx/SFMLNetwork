#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include<winsock2.h>
#include <mutex>
#include "Connection.h"
#include <vector>
#include "Packet.h"
#define BUFLEN 512  //Max length of buffer
#define SEND_DELAY 0.001f
#define RECEIVE_DELAY 0.001f
class Network
{
	struct PacketData
	{ 
		std::string data;
		Connection *connection;
	 };
	friend class Connection;
public:
	Network(std::string ip, unsigned short port, bool server);
	~Network();
	void Initialize();

	Connection localConnection;
	std::vector<Connection*> *getConnections(){ return &connections; }
private:
	void Send(Connection *connection, std::string data);
	void InitializeServer();
	void InitializeClient();
	void InitializeThreads();
	void ReceiveThread();
	void SendThread();
	std::string ip;
	unsigned int port;
	SOCKET socketThis;
	bool server;

	std::vector<Connection*> connections;

	//Send and receive
	std::vector<PacketData> outData;
	std::vector<PacketData> inData;
	std::mutex outDataMutex;
	std::mutex inDataMutex;

	bool threadsRunning;
	Timer sendTimer;
	Timer receiveTimer;


	Connection *findConnection(std::string ip,std::string port);
};

