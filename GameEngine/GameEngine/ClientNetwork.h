#pragma once
#include "../Core/NetworkServices.h"
#include <WS2tcpip.h>
#include <stdio.h>


#define DEFAULT_BUFFER_LENGTH 512
#define DEFAULT_PORT "50001"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
class ClientNetwork
{
public:
	ClientNetwork();
	~ClientNetwork();

	int RecievePackets(char* Buffer);

	int iResult;

	SOCKET ConnectionSocket;
};

