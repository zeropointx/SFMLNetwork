#pragma once
class PlayerData
{
public:
	PlayerData();
	~PlayerData();
	int x;
	int y;
	int id;
private:
	static int currentId;

};

