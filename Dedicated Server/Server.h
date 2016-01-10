#pragma once
#include "Network.h"
#include "PlayerData.h"
#include "CoordinatePacket.h"
#include "InitializePlayerPacket.h"
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
	InitializePlayerPacket *initPlayerPacket;
	CoordinatePacket *coordPacket;
	std::vector<Player> players;
	unsigned short port;

};

