#pragma once
#include "SceneParent.h"
#include "Network.h"
class GameScene :
	public SceneParent
{
	friend class CommandHandler;
public:
	GameScene(std::string ip, unsigned short port, sf::RenderWindow *window);
	~GameScene();
	void Update(float dt);
	void Draw();
	void Start();
private:
	Network *network;
	sf::RectangleShape *background;
	void setTexture(std::string name, sf::RectangleShape *rect, sf::Vector2f size);
};

