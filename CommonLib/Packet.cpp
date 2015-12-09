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

	int index = 0;

	//Push packetiD!
	u_long number = htonl(packet->packetId);
	*((u_long *)(&p[index])) = number;
	index += sizeof(u_long);



	for (auto it = variableTypes.begin(); it != variableTypes.end(); it++)
	{ 
		switch ((*it))
		{
			case UINT:
			{
				u_long number = htonl(va_arg(argumentList, unsigned int));
				*((u_long *)(&p[index])) = number;
				index += sizeof(unsigned int);
				continue;
			}
			case INT:
			{
				u_long number = htonl(va_arg(argumentList, int));
				*( (u_long *) (&p[index]) ) = number;
				/*u_long number2 = *((u_long*)(&p[0]));
				std::string testi;
				for (int i = 0; i < 4; i++)
				{
					testi += p[i];
				}
				u_long number3 = *((u_long*)(&testi.c_str()[0]));*/
				index += sizeof(u_long);
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
	std::string returnString;
	for (int i = 0; i < index; i++)
	{
		returnString += p[i];
	}
	return returnString;
}

std::vector<std::string> Packet::deSerialize(std::string data)
{
	std::vector<std::string> returnVector;
	int index = 0;

	for (auto it = variableTypes.begin(); it != variableTypes.end(); it++)
	{
		switch ((*it))
		{
			case UINT:
			{
				//FIrst get from string and convert it to actual u_long
				u_long number = ntohl(*((u_long*)(&data.c_str()[index])));
				//Then create char array with size of u_long
				char *p = (char*)malloc(sizeof(u_long));
				//Put that long in there
				*((u_long *)(&p[index])) = number;
				//and conver it back to string
				std::string intString;
				for (int i = 0; i < sizeof(u_long); i++)
				{
					intString += p[i];
				}
				//And push back
				returnVector.push_back(intString);

				index += sizeof(u_long);
				continue;
			}
			case INT:
			{
				//FIrst get from string and convert it to actual u_long
				u_long number = ntohl(   *(  (u_long*) (&data.c_str()[index])  )    );
				//Then create char array with size of u_long
				char *p =  (char*)malloc(sizeof(u_long));
				//Put that long in there
				*((u_long *)(&p[index])) = number;
				//and conver it back to string
				std::string intString;
				for (int i = 0; i < sizeof(u_long); i++)
				{
					intString += p[i];
				}
				//And push back
				returnVector.push_back(intString);

				index += sizeof(u_long);
				continue;
			}
			case STRING:
			{
				//FIrst get from string and convert it to actual u_long
				const char *charData = &(data.c_str()[index]);
			
				std::string charString;
				int tempIndex = 0;
				while (charData[tempIndex] != '\0')
				{
					charString += charData[tempIndex];
					tempIndex++;
				}
			
				returnVector.push_back(charString);

				index += sizeof(char) * charString.size() + 1;
				continue;
			}
			case CHAR:
			{
				char charred = data.c_str()[index];
				returnVector.push_back(std::string(""+charred));
				index += sizeof(char);
				continue;
			}
			default:
			{
					assert(false);
			}
		}

	}
	return returnVector;
}
