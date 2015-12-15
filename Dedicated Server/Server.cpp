#include "Server.h"
#include "InitializePlayerPacket.h"
#include <iostream>
#include "ClientStatePacket.h"
#include "Utility.h"
Server *Server::serverInstance = nullptr;
Server::Server(unsigned short port)
{
	this->port = port;
	network = new Network("127.0.0.1", port, true);
	coordPacket = new CoordinatePacket();
}


Server::~Server()
{
}
Server *Server::getServer()
{
	return serverInstance;
}
void Server::Update()
{
	ClientStatePacket packet;

	InitializePlayerPacket *initPlayerPacket = new InitializePlayerPacket();
	std::vector<Connection*> *newconnections =network->getNewConnections();
	std::vector<Connection*> *connections =network->getConnections();
	if (newconnections->size() > 0)
	{
		for (int i = 0; i < newconnections->size(); i++)
		{
			Player player;
			player.pdata = PlayerData();
			player.conn = newconnections->at(i);
			
			newconnections->at(i)->Send(&packet, player.pdata.id);
				players.push_back(player);
			
		}
		newconnections->clear();
	}


	auto data = network->getPacketHandler()->getPacketData();
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].packet->getId() == packet.getId())
		{
			//Get player
			Player *p = nullptr;;
			std::string playerString = data[i].conn->getIp() + ":" + std::to_string(data[i].conn->getPort());
			for (int j = 0; j < players.size(); j++)
			{
				std::string anotherPlayerString = players[j].conn->getIp() + ":" + std::to_string(players[j].conn->getPort());
				if (strcmp(playerString.c_str(), anotherPlayerString.c_str()) == 0)
				{
					p = &players[j];
					break;
				}
			}
			if (p == nullptr)
			{
				std::cout << "ERROR" << std::endl;
				return;
			}
			for (int j = 0; j < network->getConnections()->size(); j++)
			{
			
				if (network->getConnections()->at(j) != nullptr)
				{
					network->getConnections()->at(j)->Send(initPlayerPacket, p->pdata.id, p->pdata.x, p->pdata.y);
				}
			}
		}
		if (data[i].packet->getId() == coordPacket->getId())
		{
			int id = Utility::networkToUlong(data[i].packetData[0]);
			int x = (int)Utility::networkToUlong(data[i].packetData[1]);
			int y = (int)Utility::networkToUlong(data[i].packetData[2]);
			for (int j = 0; j < network->getConnections()->size(); j++)
			{

				if (network->getConnections()->at(j) != nullptr)
				{
					network->getConnections()->at(j)->Send(coordPacket, id, x ,y);
				}
			}
		}
	}
	
}