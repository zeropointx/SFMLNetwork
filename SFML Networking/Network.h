#pragma once
#include <string>
#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
class Packet;
class Network
{

public:
	Network(std::string ip, unsigned short port);
	~Network();
	void Initialize();
	void Send(std::string message);
	void Send(Packet *p,...);
private:
	std::string ip;
	unsigned short port;
	struct sockaddr_in si_other;
	int s, slen;

};

