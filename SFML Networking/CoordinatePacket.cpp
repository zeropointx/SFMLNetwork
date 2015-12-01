#include "CoordinatePacket.h"


CoordinatePacket::CoordinatePacket() : Packet(std::vector <Packet::VariableType> {INT, INT})
{
}


CoordinatePacket::~CoordinatePacket()
{
}
