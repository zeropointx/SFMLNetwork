#include "PlayerData.h"
int PlayerData::currentId = 0;

PlayerData::PlayerData()
{
	x = 0;
	y = 0;
	id = currentId++;
}


PlayerData::~PlayerData()
{
}
