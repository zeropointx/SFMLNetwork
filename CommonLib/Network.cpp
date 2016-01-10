#include "Network.h"

#include <varargs.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <thread>
#include<iostream>
Network::Network(std::string ip, unsigned short port, bool server) : localConnection(this)
{
	packetHandler = new PacketHandler(this);
	this->ip = ip;
	this->port = port; 
	this->server = server;
	send_delay = 0.000f;
	receive_delay = 0.000f;
	Initialize();
}


Network::~Network()
{
	threadsRunning = false;
	closesocket(socketThis);
	delete packetHandler;
}
void Network::Initialize()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if ((socketThis = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	threadsRunning = true;

	memset((char *)&localConnection.socketAddr, 0, sizeof(localConnection.socketAddr));
	localConnection.socketAddr.sin_family = AF_INET;
	localConnection.socketAddr.sin_addr.s_addr = INADDR_ANY;
	if (server)
	{
		InitializeServer();
	}
	else
	{
		InitializeClient();
	}

	InitializeThreads();
}
void Network::InitializeServer()
{
	localConnection.socketAddr.sin_port = htons(port);
	if (bind(socketThis, (struct sockaddr *)&localConnection.socketAddr, sizeof(localConnection.socketAddr)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}
void Network::InitializeClient()
{
	//Set local parameters
	localConnection.socketAddr.sin_port = htons(0);

	//Create server connection
	struct sockaddr_in remoteAddr;
	memset((char *)&remoteAddr, 0, sizeof(remoteAddr));
	remoteAddr.sin_family = AF_INET;
	remoteAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	remoteAddr.sin_port = htons(port);

	//Add server connection to list
	Connection *server = new Connection(this);
	server->socketAddr = remoteAddr;
	connections.push_back(server);

	if (bind(socketThis, (struct sockaddr *)&localConnection.socketAddr, sizeof(localConnection.socketAddr)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}
void Network::InitializeThreads()
{
	std::thread receive(&Network::ReceiveThread, this);
	receive.detach();
	std::thread send(&Network::SendThread, this);
	send.detach();
}
void Network::ReceiveThread()
{
	struct sockaddr_in socketAddrOther;
	memset((char *)&socketAddrOther, 0, sizeof(socketAddrOther));
	int socketAddrLength = sizeof(socketAddrOther);
	char buf[BUFLEN];
	receiveTimer.start();
	while (threadsRunning)
	{
		if (receiveTimer.getCurrentTimeSeconds() >= receive_delay)
		{
			memset(buf, '\0', BUFLEN);
			int dataCountReceived;
			if ((dataCountReceived = recvfrom(socketThis, buf, BUFLEN, 0, (struct sockaddr *) &socketAddrOther, &socketAddrLength)) == SOCKET_ERROR)
			{
				printf("recvfrom() failed with error code : %d\n", WSAGetLastError());
			}
			else{
				inDataMutex.lock();
				u_short tempPort = ntohs(socketAddrOther.sin_port);
				std::string portString = std::to_string(tempPort);
				char *tempIP = inet_ntoa(socketAddrOther.sin_addr);
				Connection *conn = new Connection(this);
				conn->socketAddr = socketAddrOther;
				if (findConnection(ip, portString) == nullptr)
				{
					//Do something with received client

					connections.push_back(conn);
					newConnections.push_back(conn);
				}
				PacketData pdata;
				pdata.connection = conn;
				pdata.data = std::string(&buf[0], &buf[dataCountReceived]);
				inData.push_back(pdata);
			//	std::cout << "Message received: " << buf << std::endl;
				inDataMutex.unlock();
			}
			receiveTimer.start();
		}
	}
}
void Network::SendThread()
{
	sendTimer.start();
	while (threadsRunning)
	{
		if (sendTimer.getCurrentTimeSeconds() >= send_delay)
		{
			outDataMutex.lock();
			while (outData.size() > 0)
			{
				
				std::string message = outData[0].data;
				Connection *connection = outData[0].connection;
				if (sendto(socketThis, message.c_str(), message.size(), 0, (struct sockaddr *) &connection->socketAddr, sizeof(connection->socketAddr)) == SOCKET_ERROR)
				{
					printf("sendto() failed with error code : %d", WSAGetLastError());
				}
				outData.erase(outData.begin());
				
			}
			outDataMutex.unlock();
			sendTimer.start();
		}
	}
	
}
Connection *Network::findConnection(std::string ip,std::string port)
{
	std::string playerString = ip + ":" + port;
	for (int i = 0; i < connections.size(); i++)
	{
		std::string anotherPlayerString = connections[i]->getIp() + ":" + std::to_string(connections[i]->getPort());
		if (strcmp(playerString.c_str(), anotherPlayerString.c_str()) == 0)
		{
			return connections[i];
		}
	}
	return nullptr;
}
void Network::Send(Connection *connection,std::string data)
{
	PacketData packetData;
	packetData.data = data;
	packetData.connection = connection;
	//Mutex protected push
	outDataMutex.lock();
	outData.push_back(packetData);
	outDataMutex.unlock();
}
void Network::setSendDelay(float newDelay)
{
	send_delay = newDelay;
}
void Network::setReceiveDelay(float newDelay)
{
	receive_delay = newDelay;
}