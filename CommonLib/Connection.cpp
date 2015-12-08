#include "Connection.h"
#include "Packet.h"
#include "Network.h"
Connection::Connection(Network *network)
{
	state = CONNECTED;
	this->network = network;
}


Connection::~Connection()
{
}
std::string Connection::getIp()
{
	return std::string(inet_ntoa(socketAddr.sin_addr));
}
unsigned int Connection::getPort()
{
	return 	ntohs(socketAddr.sin_port);
}
bool Connection::isTimedOut()
{
	if (timeOutTimer.getCurrentTimeSeconds() > CONNECTION_LOST_TIME)
		return true;
	return false;
}
void Connection::Send(Packet *packet, ...)
{
	va_list argList;

	va_start(argList, packet);
	std::string data = packet->toString(packet, argList);
	va_end(argList);
	network->Send(this, data);
}