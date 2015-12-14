#pragma once
#include <vector>
#include <stdarg.h>
#define BUFLEN 512  //Max length of buffer
class Packet
{
	friend class Network;
	friend class PacketHandler;
public:
	enum SizeType
	{
		FIXED,
		VAR
	};
	enum VariableType
	{
		UINT,
		INT,
		STRING,
		FLOAT,
		CHAR
	};
	Packet(std::vector<VariableType> variableTypes);
	~Packet();
	size_t getSize();
	std::string toString(Packet *packet,va_list argumentList);
	std::vector<std::string> deSerialize(std::string data);
	int getId();
protected:
	unsigned int packetId;
	size_t size;
	SizeType sizeType;
	std::vector<VariableType> variableTypes;
	size_t getSize(VariableType type);
};

