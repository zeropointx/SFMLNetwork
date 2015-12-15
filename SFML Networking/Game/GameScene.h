#pragma once
#include "SceneParent.h"
#include "Network.h"
#include "InitializePlayerPacket.h"
#include "PlayerData.h"
#include "CoordinatePacket.h"
#include "ClientStatePacket.h"
#include "Timer.h"
class GameScene :
	public SceneParent
{
	friend class CommandHandler;
public:
	struct Player
	{
		PlayerData pData;
		Connection *conn;
		sf::RectangleShape *circle;
	};
	GameScene(std::string ip, unsigned short port, sf::RenderWindow *window);
	~GameScene();
	void Update(float dt);
	void Draw();
	void Start();
private:
	float sendDelay;
	Timer sendTimer;
	int myId;
	CoordinatePacket *coordPacket;
	ClientStatePacket *clientState;
	std::vector<Player> players;
	InitializePlayerPacket *initPlayer;
	Network *network;
	sf::RectangleShape *background;
	void setTexture(std::string name, sf::RectangleShape *rect, sf::Vector2f size);
};

