#pragma once
#include "Network.h"
class Server
{
	
	friend class CommandHandler;
public:
	static Server* getServer();
	Server(unsigned short port);
	~Server();
	static Server* serverInstance;
private:

	unsigned short port;
	Network *network;
};

