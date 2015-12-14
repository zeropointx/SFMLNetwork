#pragma once
#include "Packet.h"
class ClientStatePacket : public Packet
{
public:
	enum State
	{
		LOGIN,
		LOGOUT
	};
	ClientStatePacket();
	~ClientStatePacket();
};

