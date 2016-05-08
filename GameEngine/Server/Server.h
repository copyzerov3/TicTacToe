#pragma once
#include "ServerNetwork.h"
#include <vector>
class Server
{
public:
	Server();
	~Server();
	void Update();
	void RecieveFromClients();
	void SendPacketToAll(unsigned int packetType);
	std::vector<unsigned int> Events;
private:
	static unsigned int client_ID;

	ServerNetwork* Network;

	char NetworkData[MAX_PACKET_SIZE];
};

