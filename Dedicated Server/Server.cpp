#include "Server.h"
#include "InitializePlayerPacket.h"
#include <iostream>
#include "ClientStatePacket.h"
Server *Server::serverInstance = nullptr;
Server::Server(unsigned short port)
{
	this->port = port;
	network = new Network("127.0.0.1", port, true);
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
	std::vector<Connection*> *newconnections =network->getNewConnections();
	std::vector<Connection*> *connections =network->getConnections();
	if (newconnections->size() > 0)
	{
		for (int i = 0; i < newconnections->size(); i++)
		{
			PlayerData player;
			for (int j = 0; j < connections->size(); j++)
			{
				connections->at(j)->Send(&packet, player.id, 0, 0);
			}
		}
		newconnections->clear();
	}


	auto data = network->getPacketHandler()->getPacketData();
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].packet->getId() == packet.getId())
		{

		}
		std::cout << "SIZE: " << data[i].packetData.size() << std::endl;
	}
	
}