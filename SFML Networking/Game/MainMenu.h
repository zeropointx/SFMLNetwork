#pragma once
#include <SFML/Graphics.hpp>
#include "SceneParent.h"
class MainMenu :
	public SceneParent
{
public:
	MainMenu(sf::RenderWindow *window);
	~MainMenu();
	void Update(float dt);
	void Draw();
	void Start();
private:
	sf::RectangleShape toniplz;
	sf::RectangleShape connect_nappi;
	void setTexture(std::string name, sf::RectangleShape *rect);
};

