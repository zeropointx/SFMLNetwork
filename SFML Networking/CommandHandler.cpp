#include "CommandHandler.h"
#include <thread>
#include <iostream>

#include <sstream>

#include "Game\SceneSys.h"
#include "Game\GameScene.h"
#include "CoordinatePacket.h"
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
		GameScene *scene = dynamic_cast<GameScene*>(SceneSys::GetScene(0));
		if (scene != nullptr)
		{
			CoordinatePacket packet;
			scene->network->connections[0]->Send(&packet, 555, 555);
			std::cout << "Sending packet!" << std::endl;
		}
	}
}