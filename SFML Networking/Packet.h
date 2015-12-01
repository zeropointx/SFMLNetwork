#pragma once
#include <vector>
#define BUFLEN 512  //Max length of buffer
class Packet
{
	
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
	std::string Send(unsigned int packetId,...);
private:
	unsigned int packetId;
	size_t size;
	SizeType sizeType;
	std::vector<VariableType> variableTypes;
	size_t getSize(VariableType type);
};

