#include "Network.h"
#include <string>
#include "CoordinatePacket.h"
int main()
{
	Network *network = new Network("127.0.0.1",8888,true);
	CoordinatePacket *packet = new CoordinatePacket();
	int i = 0;
	while (true)
	{
		i++;
		auto connections = network->getConnections();
		if (i % 1000000000 == 0)
			connections->at(0)->Send(packet, 555, 555);
	}
}