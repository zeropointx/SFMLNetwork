#pragma once
class PlayerData
{
public:
	PlayerData();
	~PlayerData();
	float x;
	float y;
	int id;
private:
	static int currentId;

};

