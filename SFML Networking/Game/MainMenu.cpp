#include "MainMenu.h"
#include <iostream>
MainMenu::MainMenu(sf::RenderWindow *window) : SceneParent(window)
{
	toniplz = sf::RectangleShape(sf::Vector2f(100, 100));
	setTexture("perfect_doge.png", &toniplz);



	connect_nappi = sf::RectangleShape(sf::Vector2f(100, 100));
	setTexture("connect_nappi.png", &connect_nappi);
	sf::Vector2u screenSize = window->getSize();
	connect_nappi.setOrigin(connect_nappi.getSize() / 2.0f);
	connect_nappi.setPosition(screenSize.x / 2, screenSize.y / 5);
}


MainMenu::~MainMenu()
{
}
void MainMenu::Update(float dt)
{
	sf::Vector2f pos = connect_nappi.getPosition();
	sf::Vector2f size = connect_nappi.getSize();
	sf::Vector2f orig = connect_nappi.getOrigin();
	sf::Rect<float> rect = sf::Rect<float>(pos.x - orig.x, pos.y -orig.y,size.x ,size.y );
	sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
	sf::Vector2<float> mousePos_VITTU_CONVERTED_KOSKA_PASKA_SFML = sf::Vector2<float>(mousePos.x, mousePos.y);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (rect.contains(mousePos_VITTU_CONVERTED_KOSKA_PASKA_SFML))
		{
			std::cout << "Olen passi" << std::endl;
		}
	}
	
}
void MainMenu::Draw()
{
	_window->draw(toniplz);
	_window->draw(connect_nappi);
	

}
void MainMenu::Start()
{

}
void MainMenu::setTexture(std::string name, sf::RectangleShape *rect)
{
	sf::Texture *texture = new sf::Texture();
	texture->loadFromFile(name);
	rect->setTexture(texture);

	rect->setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
	rect->setTexture(texture);
}