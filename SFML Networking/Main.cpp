#include <SFML/Graphics.hpp>
#include "Network.h"
#include <iostream>
#include <string>
#include <thread>
#include "Network\CoordinatePacket.h"
#include "Game\SceneSys.h"
#include "Game\MainMenu.h"
#include "Timer.h"
void NetworkThread();
int main()
{
	std::thread networkThread(NetworkThread);
	networkThread.detach();
	sf::Vector2f desktopRes= sf::Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	sf::RenderWindow window(sf::VideoMode(desktopRes.x/2, desktopRes.y/2), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	SceneSys::ChangeScene(new MainMenu());
	Timer deltaTime;
	//PLEASEREMOVE *remove = new PLEASEREMOVE();
	deltaTime.start();
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float passedTime = deltaTime.getCurrentTimeSeconds();
		SceneSys::Update(passedTime);

			deltaTime.start();
		window.clear();
		SceneSys::Draw();
		//window.draw(shape);
		window.display();
		
	}

	system("PAUSE");
	return 0;
}
void NetworkThread()
{
	
	Network network("127.0.0.1", 8888,false);
	CoordinatePacket *packet = new CoordinatePacket();
	network.Send(packet, 555, 555);
	while (true)
	{
		std::cout << " Give a message: " << std::endl;
		std::string data;
		getline(std::cin, data);
		//network.Send(std::string(data));
	}
}