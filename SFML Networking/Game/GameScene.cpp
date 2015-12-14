#include "GameScene.h"
#include "CoordinatePacket.h"
#include "ClientStatePacket.h"
GameScene::GameScene(std::string ip, unsigned short port, sf::RenderWindow *window): SceneParent(window)
{
	network = new Network(ip, port, false);
	
	ClientStatePacket *clientState = new ClientStatePacket();
	network->getConnections()->at(0)->Send(clientState, ClientStatePacket::LOGIN);

	background = new sf::RectangleShape();
	sf::Vector2f windowSize = sf::Vector2f(window->getSize().x, window->getSize().y);
	setTexture("background_doge.jpg", background, windowSize);
}


GameScene::~GameScene()
{
}
void GameScene::Update(float dt)
{

}
void GameScene::Draw()
{
	_window->draw(*background);
}
void GameScene::Start()
{

}
void GameScene::setTexture(std::string name, sf::RectangleShape *rect, sf::Vector2f size)
{
	sf::Texture *texture = new sf::Texture();
	texture->loadFromFile(name);
	rect->setTexture(texture);

	rect->setSize(size);
	rect->setTexture(texture);
}