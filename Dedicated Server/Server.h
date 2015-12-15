#pragma once
#include "Network.h"
#include "PlayerData.h"
#include "CoordinatePacket.h"
class Server
{
	
	friend class CommandHandler;
public:
	struct Player{
		PlayerData pdata;
		Connection *conn;
	};
	static Server* getServer();
	Server(unsigned short port);
	~Server();
	static Server* serverInstance;
	Network *network;
	void Update();
private:
	CoordinatePacket *coordPacket;
	std::vector<Player> players;
	unsigned short port;

};

