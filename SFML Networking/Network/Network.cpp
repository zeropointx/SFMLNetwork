#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "Network.h"
#include "Packet.h"
#include<thread>
#define BUFLEN 512  //Max length of buffer
void ThreadReceive(unsigned short socket);
Network::Network(std::string ip, unsigned short port)
{
	this->ip = ip;
	this->port = port;
	Initialize();
}


Network::~Network()
{
}
void Network::Initialize()
{
	slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port);
	si_other.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	//bind(s, (struct sockaddr*)&si_other, slen);
	Send("0");
	std::thread thread(ThreadReceive,s);
	thread.detach();
}
void ThreadReceive(unsigned short socket)
{
	struct sockaddr_in si_other2;
	int slen2 = sizeof(si_other2);
	char buf[BUFLEN];
	while (true)
	{
		memset(buf, '\0', BUFLEN);
		if (recvfrom(socket, buf, BUFLEN, 0, (struct sockaddr *) &si_other2, &slen2) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d\n", WSAGetLastError());
		}
		else{
			printf("Message received: %s", buf);
		}
		memset(buf, '\0', BUFLEN);
		
	}
}
void Network::Send(std::string message)
{
	if (sendto(s, message.c_str(), message.size(), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
	}
}
void Network::Send(Packet *p,...)
{
	va_list args;
	int packetId = p->packetId;
	std::string data;
	va_start(args, p);
	data = p->toString(p, args);
	va_end(args);
	Send(data.c_str());
}