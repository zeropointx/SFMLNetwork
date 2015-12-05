#include "Network.h"


#include<stdio.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <thread>
#include<iostream>

Network::Network(std::string ip, unsigned short port, bool server)
{
	this->ip = ip;
	this->port = port; 
	this->server = server;
}


Network::~Network()
{
}
void Network::Initialize()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if ((socketThis = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if (server)
		InitializeServer();
	else
		InitializeClient();
	InitializeThreads();
}
void Network::InitializeServer()
{
	localConnection.socketAddr.sin_family = AF_INET;
	localConnection.socketAddr.sin_addr.s_addr = INADDR_ANY;
	localConnection.socketAddr.sin_port = htons(port);

	if (bind(socketThis, (struct sockaddr *)&localConnection.socketAddr, sizeof(localConnection.socketAddr)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}
void Network::InitializeClient()
{
	memset((char *)&localConnection.socketAddr, 0, sizeof(localConnection.socketAddr));
	localConnection.socketAddr.sin_family = AF_INET;
	localConnection.socketAddr.sin_port = htons(port);
	localConnection.socketAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	
}
void Network::InitializeThreads()
{
	std::thread receive(&Network::ReceiveThread, this);
	receive.detach();
}
void Network::ReceiveThread()
{
	struct sockaddr_in socketAddrOther;
	int socketAddrLength = sizeof(socketAddrOther);
	char buf[BUFLEN];
	while (true)
	{
		memset(buf, '\0', BUFLEN);
		if (recvfrom(socketThis, buf, BUFLEN, 0, (struct sockaddr *) &socketAddrOther, &socketAddrLength) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d\n", WSAGetLastError());
		}
		else{
			std::cout << "Message received: " << buf << std::endl;
		}

	}
}
void Network::SendThread()
{
	while (true)
	{
		std::string message = "";
		if (sendto(socketThis, message.c_str(), message.size(), 0, (struct sockaddr *) &localConnection.socketAddr, sizeof(localConnection.socketAddr)) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
		}
	}
	
}
Connection *Network::findConnection(std::string ip,std::string port)
{
	auto it = connections.find(ip+":"+port);
	if (it != connections.end())
	{
		return &it->second;
	}
	return nullptr;
}
void Network::Send(Packet *packet, Connection *sendTo)
{
	PacketData data;
	data.packet = packet;
	data.connection = sendTo;
	outData.push_back(data);
}