#include "CommandHandler.h"
#include <thread>
#include <iostream>

#include <sstream>

#include "CoordinatePacket.h"
#include "Server.h"
CommandHandler::CommandHandler()
{
	running = true;
	std::thread thread(&CommandHandler::commandThread,this);
	thread.detach();
}


CommandHandler::~CommandHandler()
{
}
void CommandHandler::commandThread()
{
	while (running)
	{
		std::string message;
		getline(std::cin, message);
		std::cout << "Command: " << message << std::endl;
		std::istringstream iss(message);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},

			std::istream_iterator<std::string>{} };
		handleCommand(tokens);
	}
}
void CommandHandler::handleCommand(std::vector<std::string> command)
{
	if (strcmp(command[0].c_str(), "sendData") == 0)
	{

			CoordinatePacket packet;
			Server *server = Server::getServer();
			server->network->connections[0]->Send(&packet, 555, 555);
			std::cout << "Sending packet!" << std::endl;
	}
	else if (strcmp(command[0].c_str(), "setSendDelay") == 0)
	{
		Server *server = Server::getServer();
		float delay = std::stof(command[1]);
		server->network->setSendDelay(delay);
	}
	else if (strcmp(command[0].c_str(), "setReceiveDelay") == 0)
	{
		Server *server = Server::getServer();
		float delay = std::stof(command[1]);
		server->network->setReceiveDelay(delay);
	}
}