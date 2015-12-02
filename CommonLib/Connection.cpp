#include "Connection.h"


Connection::Connection()
{
	state = CONNECTED;
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