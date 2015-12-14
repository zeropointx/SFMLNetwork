#pragma once
#include "Packet.h"
class InitializePlayerPacket :
	public Packet
{
public:
	InitializePlayerPacket();
	~InitializePlayerPacket();
};

