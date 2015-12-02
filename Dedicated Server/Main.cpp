#include "Network.h"
#include <string>
int main()
{
	Network *network = new Network("127.0.0.1",8888,true);
	network->Initialize();
	while (true)
	{

	}
}