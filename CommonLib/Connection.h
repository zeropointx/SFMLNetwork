#pragma once
#include <WinSock2.h>
#include "Timer.h"
#include <string>
#define CONNECTION_LOST_TIME 5.0f
class Packet;
class Network;
class Connection
{
	friend class Network;
	enum State
	{
		CONNECTED,
		CONNECTION_LOST,
	};
public:
	Connection(Network *network);
	~Connection();
	std::string getIp();
	unsigned int getPort();
	bool isTimedOut();
	void Send(Packet *packet, ...);
private:
	Network *network;
	struct sockaddr_in socketAddr;
	Timer timeOutTimer;
	State state;
};

