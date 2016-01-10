#include "GameScene.h"

#include "Utility.h"
GameScene::GameScene(std::string ip, unsigned short port, sf::RenderWindow *window): SceneParent(window)
{
	network = new Network(ip, port, false);
	
	clientState = new ClientStatePacket();
	initPlayer = new InitializePlayerPacket();
	coordPacket = new CoordinatePacket();
	network->getPacketHandler()->addPacketTemplate(initPlayer);
	network->getPacketHandler()->addPacketTemplate(clientState);
	network->getPacketHandler()->addPacketTemplate(coordPacket);
	network->getConnections()->at(0)->Send(clientState, ClientStatePacket::LOGIN);

	background = new sf::RectangleShape();
	sf::Vector2f windowSize = sf::Vector2f(window->getSize().x, window->getSize().y);
	setTexture("background_doge.jpg", background, windowSize);
	sendDelay = 0.1f;
	sendTimer.start(); 
}


GameScene::~GameScene()
{
}
void GameScene::Update(float dt)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].circle->getPosition() != players[i].targetPos)
		{
			sf::Vector2f lerpValue = Lerp(players[i].circle->getPosition(), players[i].targetPos, 1.0f / 30.0f);
			players[i].circle->setPosition(lerpValue);
		}
	}



	auto data = network->getPacketHandler()->getPacketData();
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].packet->getId() == initPlayer->getId())
		{
			Player p;
			p.conn = data[i].conn;
			p.pData.id = Utility::networkToUlong(data[i].packetData[0]);
			p.pData.x = Utility::networkToUlong(data[i].packetData[1]);
			p.pData.y = Utility::networkToUlong(data[i].packetData[2]);
			p.targetPos.x = p.pData.x;
			p.targetPos.y = p.pData.y;
			p.circle = new sf::RectangleShape();
			setTexture("doge.jpg", p.circle, sf::Vector2f(100, 100));
			players.push_back(p);
		}
		else if (data[i].packet->getId() == clientState->getId())
		{
			myId = Utility::networkToUlong(data[i].packetData[0]);
		}
		else if (data[i].packet->getId() == coordPacket->getId())
		{
			int id = Utility::networkToUlong(data[i].packetData[0]);
			int x = Utility::networkToUlong(data[i].packetData[1]);
			int y = Utility::networkToUlong(data[i].packetData[2]);
			for (int j = 0; j < players.size(); j++)
			{
				if (players[j].pData.id == id)
				{
					if (x == 2)
						x = -1;
					if (y == 2)
						y = -1;
					players[j].targetPos.x += (x * 10.1f);
					players[j].targetPos.y += (y * 10.1f);
				}
			}
		}
	}
	if (sendTimer.getCurrentTimeSeconds() < sendDelay)
		return;
	sendTimer.start();
	int x = 0, y = 0;
	if (_window->hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		x = 1;
	}
	else if (_window->hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		x = 2;
	}
	if (_window->hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		y = 2;
	}
	else if (_window->hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		y = 1;
	}
	if (!(x == 0 && y == 0))
		network->getConnections()->at(0)->Send(coordPacket, myId, x, y);


}
void GameScene::Draw()
{
	_window->draw(*background);
	for (int i = 0; i < players.size(); i++)
	{
		//players[i].circle->setPosition((float)players[i].pData.x, (float)players[i].pData.y);
		_window->draw(*players[i].circle);
	}

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
sf::Vector2f GameScene::Lerp(sf::Vector2f start, sf::Vector2f end, float percent)
{
	return (start + percent*(end - start));
}