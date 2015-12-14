#pragma once
#include "Network.h"
#include "PlayerData.h"
class Server
{
	
	friend class CommandHandler;
public:
	static Server* getServer();
	Server(unsigned short port);
	~Server();
	static Server* serverInstance;
	Network *network;
	void Update();
private:
	std::vector<PlayerData> players;
	unsigned short port;

};

