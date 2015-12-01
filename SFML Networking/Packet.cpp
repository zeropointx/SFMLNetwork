#include "Packet.h"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <sstream>
Packet::Packet(std::vector<VariableType> variableTypes)
{
	
	size = 0;
	//add packetId
	//variableTypes.insert(variableTypes.begin(), UINT);
	//push back /0 in the end
	//variableTypes.push_back(CHAR);
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
std::string Packet::Send(unsigned int packetId,...)
{
	va_list argumentList;
	va_start(argumentList, packetId);
	//char *p = (char*)malloc(size);
	std::ostringstream oss;
	int index = 0;
	oss<<packetId;
	for (auto it = variableTypes.begin(); it != variableTypes.end(); it++)
	{ 
		switch ((*it))
		{
		case UINT:
			//*((unsigned int *)(&p[index])) = va_arg(argumentList, unsigned int);
			//index += getSize(UINT);
			oss<<va_arg(argumentList, unsigned int);
			continue;
		case INT:
			//*((int *)(&p[index])) = va_arg(argumentList, int);
			//index += getSize(INT);
			oss << va_arg(argumentList, int);
			continue;
		case STRING:
			//*((int *)(&p[index])) = va_arg(argumentList, std::string);
			//index += getSize(STRING);
			oss << va_arg(argumentList, std::string);
			continue;
		case CHAR:
			//*((char *)(&p[index])) = va_arg(argumentList, char);
			//index += getSize(CHAR);
			oss << va_arg(argumentList, char);
			continue;
		default:
			assert(false);
		}
		
	}
	va_end(argumentList);
	
	//*((char*)(&p[index])) = '\0';
	return oss.str();
}