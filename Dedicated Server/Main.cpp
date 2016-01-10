#include "Network.h"
#include <string>
#include "CoordinatePacket.h"
#include "InitializePlayerPacket.h"
#include "Server.h"
#include <iostream>
#include <string>
#include "CommandHandler.h"
#include <vector>
#include "InitializePlayerPacket.h"
#include "PlayerData.h"
#include "ClientStatePacket.h"
int main()
{
	std::cout << "Give port:" << std::endl;
	std::string port = "8888";
//	getline(std::cin, port);
	
	int number = stoi(port);
	Server server(stoi(port));
	CommandHandler commandHandler;
	server.serverInstance = &server;



	CoordinatePacket *coordPacket = new CoordinatePacket();
	InitializePlayerPacket *initPlayerPacket = new InitializePlayerPacket();
	ClientStatePacket *clientStatePacket = new ClientStatePacket();
	server.network->getPacketHandler()->addPacketTemplate(coordPacket);
	server.network->getPacketHandler()->addPacketTemplate(initPlayerPacket);
	server.network->getPacketHandler()->addPacketTemplate(clientStatePacket);
	while (true)
	{
		server.Update();
//		Server::getServer()->network->parsePackets();
	}
	/*CoordinatePacket *packet = new CoordinatePacket();
	int i = 0;
	while (true)
	{
		i++;
		auto connections = network->getConnections();
		if (i % 100000000 == 0)
			connections->at(0)->Send(packet, 555, 555);
	}*/
}