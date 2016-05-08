#pragma once
#include "ClientNetwork.h"
#include <vector>
class Client
{
public:
	Client();
	~Client();

	void SendPackets(unsigned int packetType);

	char NetworkData[MAX_PACKET_SIZE];

	void Update();

	ClientNetwork* Network;
	
	std::vector<unsigned int> Events;
};

