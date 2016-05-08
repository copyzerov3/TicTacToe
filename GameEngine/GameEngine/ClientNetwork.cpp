#include "ClientNetwork.h"


ClientNetwork::ClientNetwork()
{
	WSADATA wsaData;

	ConnectionSocket = INVALID_SOCKET;

	// holds address info for socket to connect to
	struct addrinfo *result = NULL,*ptr = NULL,hints;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0)
	{
		printf("WSAStartup failed with error %d\n", iResult);
		exit(1);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed with error %d\n", iResult);
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		ConnectionSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectionSocket == INVALID_SOCKET)
		{
			printf("Socket Failed with error %d\n", WSAGetLastError());
			WSACleanup();
			exit(1);
		}

		iResult = connect(ConnectionSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectionSocket);
			ConnectionSocket = INVALID_SOCKET;
			printf("The server is down, can not connect, TURN THE SERVER ON FIRST\n");
		}
	}
	freeaddrinfo(result);

	if (ConnectionSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server currently\n");
		WSACleanup();
		exit(1);
	}
	u_long iMode = 1;

	iResult = ioctlsocket(ConnectionSocket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR)
	{
		printf("setting to non blocking failed with error %d\n", WSAGetLastError());
		closesocket(ConnectionSocket);
		WSACleanup();
		exit(1);
	}
	//turn off optimization for now.
	char value = 1;
	setsockopt(ConnectionSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
}


ClientNetwork::~ClientNetwork()
{
}

int ClientNetwork::RecievePackets(char* Buffer)
{
	iResult = NetworkServices::RecieveMessage(ConnectionSocket, Buffer, MAX_PACKET_SIZE);

	if (iResult == 0)
	{
		printf("Connection with server closed\n");
		closesocket(ConnectionSocket);
		WSACleanup();
		exit(1);
	}
	return iResult;
}
