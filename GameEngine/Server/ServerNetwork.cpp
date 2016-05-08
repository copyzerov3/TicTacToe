#include "ServerNetwork.h"

ServerNetwork::ServerNetwork()
{
	WSADATA wsaData;

	ListenSocket = INVALID_SOCKET;
	ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartuo failed with error %d\n", iResult);
		exit(1);
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed with error %d\n", iResult);
		WSACleanup();
		exit(1);
	}
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET)
	{
		printf("ListenSocket failed with error %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}

	u_long iMode = 1;
	iResult = ioctlsocket(ListenSocket, FIONBIO, &iMode);

	if (iResult == SOCKET_ERROR) 
	{
		printf("ioctlsocket failed to set to non blocking with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);

	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}
}


ServerNetwork::~ServerNetwork()
{
	if (ListenSocket != INVALID_SOCKET)
	{
		closesocket(ListenSocket);
	}
	if (ClientSocket != INVALID_SOCKET)
	{
		closesocket(ClientSocket);
	}
	WSACleanup();
}


bool ServerNetwork::AcceptNewClient(unsigned int& id)
{
	ClientSocket = accept(ListenSocket, NULL, NULL);
	
	if (ClientSocket != INVALID_SOCKET)
	{
		char value = 1;
		setsockopt(ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

		Clients.insert(std::pair<unsigned int, SOCKET>(id, ClientSocket));
		return true;
	}
	return false;
}
int ServerNetwork::RecieveData(unsigned int ClientID, char* Buffer)
{
	if (Clients.find(ClientID) != Clients.end())
	{
		ClientSocket = Clients[ClientID];
		iResult = NetworkServices::RecieveMessage(ClientSocket, Buffer, MAX_PACKET_SIZE);
		
		if (iResult == 0)
		{
			printf("Connection Closed\n");
			closesocket(ClientSocket);
		}
		return iResult;
	}

	return 0;

}

void ServerNetwork::SendToAllClients(char * packets, int totalSize)
{
	SOCKET currentSocket;
	std::map<unsigned int, SOCKET>::iterator iter;
	int iSendResult;

	for (iter = Clients.begin(); iter != Clients.end(); iter++)
	{
		currentSocket = iter->second;
		iSendResult = NetworkServices::SendMessage(currentSocket, packets, totalSize);

		if (iSendResult == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(currentSocket);
		}
	}
}