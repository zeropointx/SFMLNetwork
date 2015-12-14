#pragma once
#include "Network.h"
class PacketHandler
{
public:
	struct PacketData
	{
		Packet *packet;
		Connection *conn;
		std::vector<std::string> packetData;
	};
	PacketHandler(Network *network);
	~PacketHandler();
	std::vector<PacketData> getPacketData();
	void addPacketTemplate(Packet *packet);
private:
	Network *network;
	std::vector<Packet*> packetTemplates;
};

