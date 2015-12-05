#pragma once
#include <vector>
#include <stdarg.h>
#define BUFLEN 512  //Max length of buffer
class Packet
{
	friend class Network;
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
protected:
	unsigned int packetId;
	size_t size;
	SizeType sizeType;
	std::vector<VariableType> variableTypes;
	size_t getSize(VariableType type);
};

