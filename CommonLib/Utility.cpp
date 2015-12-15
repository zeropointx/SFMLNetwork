#include "Utility.h"


u_long Utility::networkToUlong(std::string value)
{
	return ntohl(*((u_long*)(&value.c_str()[0])));
}