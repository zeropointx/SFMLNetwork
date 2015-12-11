#include "Server.h"

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