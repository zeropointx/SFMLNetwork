#include "Network.h"
#include <string>
#include "CoordinatePacket.h"
#include "Server.h"
#include <iostream>
#include <string>
#include "CommandHandler.h"
int main()
{
	std::cout << "Give port:" << std::endl;
	std::string port;
	getline(std::cin, port);
	int number = stoi(port);
	Server server(stoi(port));
	CommandHandler commandHandler;
	server.serverInstance = &server;
	while (true)
	{

	}
	/*CoordinatePacket *packet = new CoordinatePacket();
	int i = 0;
	while (true)
	{
		i++;
		auto connections = network->getConnections();
		if (i % 100000000 == 0)
			connections->at(0)->Send(packet, 555, 555);
	}*/
}