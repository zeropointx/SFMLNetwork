#include <SFML/Graphics.hpp>
#include "Network.h"
#include "PLEASEREMOVE.h"
#include "PLEASEREMOVESERVER.h"


int main()
{
	//Network network("172.31.16.54", 8888);
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	PLEASEREMOVE *remove = new PLEASEREMOVE();
	//PLEASEREMOVESERVER *server = new PLEASEREMOVESERVER();
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