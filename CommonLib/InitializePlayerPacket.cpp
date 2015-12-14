#include "InitializePlayerPacket.h"


InitializePlayerPacket::InitializePlayerPacket() : Packet(std::vector <Packet::VariableType> {INT, INT,INT})
{
	packetId = 1;
}


InitializePlayerPacket::~InitializePlayerPacket()
{
}
