#include <SFML/Graphics.hpp>
#include "Network.h"
#include <iostream>
#include <string>
#include <thread>
#include "CoordinatePacket.h"
void NetworkThread();
int main()
{
	std::thread networkThread(NetworkThread);
	networkThread.detach();
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	//PLEASEREMOVE *remove = new PLEASEREMOVE();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	system("PAUSE");
	return 0;
}
void NetworkThread()
{
	Network network("127.0.0.1", 8888);
	CoordinatePacket packet;
	std::string data = packet.Send(0, 555, 555);
	network.Send(data.c_str());
	while (true)
	{
		std::cout << " Give a message: " << std::endl;
		std::string data;
		getline(std::cin, data);
		network.Send(std::string(data));
	}
}