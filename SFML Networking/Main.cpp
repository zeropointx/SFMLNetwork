#include <SFML/Graphics.hpp>
#include "Network.h"
#include "PLEASEREMOVE.h"
#include <iostream>
#include <string>

int main()
{
	Network network("127.0.0.1", 8888);
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	//PLEASEREMOVE *remove = new PLEASEREMOVE();
	/*while (window.isOpen())
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
	}*/
	while (true)
	{
		std::cout << " Give a message: " << std::endl;
		std::string data;
		getline(std::cin, data);
		network.Send(std::string(data));
	}
	system("PAUSE");
	return 0;
}