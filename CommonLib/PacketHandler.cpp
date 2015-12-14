#include "PacketHandler.h"
#include <mutex>

PacketHandler::PacketHandler(Network *network)
{
	this->network = network;
}


PacketHandler::~PacketHandler()
{
}
void PacketHandler::addPacketTemplate(Packet *packet)
{
	packetTemplates.push_back(packet);
}
std::vector<PacketHandler::PacketData> PacketHandler::getPacketData()
{
	std::vector<PacketHandler::PacketData> pdata;
	for (int i = 0; i < network->inData.size(); i++)
	{
		PacketHandler::PacketData packetData;
		std::string data = network->inData[i].data;
		std::vector<std::string> packetStrings;
		u_long number = *((u_long*)(&data.c_str()[0]));
		for (int j = 0; j < packetTemplates.size(); j++)
		{
			if (number == packetTemplates[j]->packetId)
			{
				packetStrings = packetTemplates[j]->deSerialize(data);
				packetData.packetData = packetStrings;
				packetData.packet = packetTemplates[j];
				packetData.conn = network->inData[i].connection;
				
				pdata.push_back(packetData);
			}
		}
	}
	std::mutex inData;
	inData.lock();
	network->inData.clear();
	inData.unlock();
	return pdata;
}