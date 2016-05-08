#pragma once
#include "PacketTypes.h"
//make Client and server Interfaces inherit from this.
class NetworkInterface
{
public:
	NetworkInterface();
	~NetworkInterface();

	virtual void Update() = 0;
	virtual void SendPacket(unsigned int PacketType);
private:

	char NetworkData[MAX_PACKET_SIZE]
};

