#pragma once
#include <NetworkServices.h>
#include <WS2tcpip.h>
#include <map>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "50001" 
class ServerNetwork
{
public:
	ServerNetwork();
	~ServerNetwork();

	bool AcceptNewClient(unsigned int& id);
	int RecieveData(unsigned int ClientID, char* Buffer);
	void SendToAllClients(char* packets, int totalSize);

	SOCKET ListenSocket;
	SOCKET ClientSocket;

	int iResult;

	std::map<unsigned int, SOCKET> Clients;
};

