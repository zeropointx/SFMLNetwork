#include "Packet.h"
#include <assert.h>
#include <stdio.h>
#include<winsock2.h>
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
	char *p;
	if (sizeType != VAR)
		p = (char*)malloc(size);
//	std::ostringstream oss;
	//oss<<packetId;
	int index = 0;
	for (auto it = variableTypes.begin(); it != variableTypes.end(); it++)
	{ 
		switch ((*it))
		{
			case UINT:
			{
				u_long number = htonl(va_arg(argumentList, unsigned int));
				*((int *)(&p[index])) = number;
				index += sizeof(unsigned int);
				continue;
			}
			case INT:
			{
				u_long number = htonl(va_arg(argumentList, int));
				*((int *)(&p[index])) = number;
				index += sizeof(int);
				continue;
			}
			case STRING:
			{
				std::string stringuli = va_arg(argumentList, std::string);
				
				strcpy(&p[index], stringuli.c_str());
				index += (stringuli.length() + 1) * sizeof(char);
				continue;
			}
			case CHAR:
			{
				char charred = va_arg(argumentList, char);
				*((char *)(&p[index])) = charred;
				index += sizeof(char);
				continue;
			}
			default:
			{
				assert(false);
			}
		}
		
	}
	return std::string(p);
}