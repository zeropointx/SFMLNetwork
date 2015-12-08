#include "Packet.h"
#include <assert.h>
#include <stdio.h>

#include <sstream>
Packet::Packet(std::vector<VariableType> variableTypes)
{
	
	size = 0;
	sizeType = FIXED;
	for (auto it = variableTypes.begin(); it != variableTypes.end(); it++)
	{
		if ((*it) == STRING)
			sizeType = VAR;
		else
		{
			size_t varSize = getSize((*it));
			assert(varSize != -1);
			size += varSize;
		}
	}
	if (sizeType == VAR)
	{
		size = BUFLEN;
	}
	this->variableTypes = variableTypes;
}


Packet::~Packet()
{
}
size_t Packet::getSize(VariableType type)
{
	switch (type)
	{
	case UINT:
		return sizeof(unsigned int);
	case INT:
		return sizeof(int);
	case CHAR:
		return sizeof(char);
	default:
		return -1;
	}
}
std::string Packet::toString(Packet *packet,va_list argumentList)
{
	std::ostringstream oss;
	oss<<packetId;
	for (auto it = variableTypes.begin(); it != variableTypes.end(); it++)
	{ 
		switch ((*it))
		{
		case UINT:
			oss<<va_arg(argumentList, unsigned int);
			continue;
		case INT:
		{
			int number = va_arg(argumentList, int);
			oss << number;
			continue;
		}
		case STRING:
			oss << va_arg(argumentList, std::string);
			continue;
		case CHAR:
			oss << va_arg(argumentList, char);
			continue;
		default:
			assert(false);
		}
		
	}
	return oss.str();
}