
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "Network.h"
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <thread>


Network::Network(unsigned int port)
{
	struct sockaddr_in server;
	char buf[BUFLEN];
	WSADATA wsa;



	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	if (bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Waiting for data..."); fflush(stdout);
	this->port = port;
	std::thread receive(&Network::ReceiveThread,this);
	receive.detach();
}


Network::~Network()
{
	closesocket(serverSocket);
	WSACleanup();
}
void Network::ReceiveThread()
{
	while (true)
	{
		int recv_len;
		struct sockaddr_in si_other;
		int slen = sizeof(si_other);
		memset(buf, '\0', BUFLEN);
		if ((recv_len = recvfrom(serverSocket, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
	}
}
void Network::SendThread()
{

}