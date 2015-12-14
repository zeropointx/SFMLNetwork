#include "ClientStatePacket.h"


ClientStatePacket::ClientStatePacket() : Packet(std::vector <Packet::VariableType> {INT})
{
	packetId = 2;
}


ClientStatePacket::~ClientStatePacket()
{
}
