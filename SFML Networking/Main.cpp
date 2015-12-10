#include <SFML/Graphics.hpp>
#include "Network.h"
#include <iostream>
#include <string>
#include <thread>
#include "CoordinatePacket.h"
#include "Game\SceneSys.h"
#include "Game\MainMenu.h"
#include "Timer.h"
#include "Connection.h"
void NetworkThread();
int main()
{

	Network network("127.0.0.1", 8888, false);
	CoordinatePacket *packet = new CoordinatePacket();
	network.getConnections()->at(0)->Send(packet, 555, 555);
	//std::thread networkThread(NetworkThread);
	//networkThread.detach();
	sf::Vector2f desktopRes= sf::Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	sf::RenderWindow window(sf::VideoMode(desktopRes.x/2, desktopRes.y/2), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	SceneSys::ChangeScene(new MainMenu(&window));
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