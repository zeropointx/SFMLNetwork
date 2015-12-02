#include "CoordinatePacket.h"


CoordinatePacket::CoordinatePacket() : Packet(std::vector <Packet::VariableType> {INT, INT})
{
	packetId = 0;
}


CoordinatePacket::~CoordinatePacket()
{
}
