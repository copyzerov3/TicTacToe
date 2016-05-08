#include "Client.h"

Client::Client()
{
	Network = new ClientNetwork();

	const unsigned int PacketSize = sizeof(Packet);
	char PacketData[PacketSize];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.Serialize(PacketData);
	NetworkServices::SendMessage(Network->ConnectionSocket, PacketData, PacketSize);
}


Client::~Client()
{
	delete Network;
	Network = NULL;
}

void Client::SendPackets(unsigned int packetType)
{
	const unsigned int packetSize = sizeof(Packet);
	char packetData[packetSize];

	Packet packet;
	packet.packet_type = packetType;

	packet.Serialize(packetData);

	NetworkServices::SendMessage(Network->ConnectionSocket, packetData, packetSize);
}

void Client::Update()
{
	Packet packet;
	int dataLength = Network->RecievePackets(NetworkData);

	if (dataLength <= 0)
	{
		return;
	}

	int i = 0;
	while (i < (unsigned int)dataLength)
	{
		packet.Deserialize(&(NetworkData[i]));
		i += sizeof(Packet);
		switch (packet.packet_type)
		{
		case CELL_PICK_ZERO:
		case CELL_PICK_ONE:
		case CELL_PICK_TWO:
		case CELL_PICK_THREE:
		case CELL_PICK_FOUR:
		case CELL_PICK_FIVE:
		case CELL_PICK_SIX:
		case CELL_PICK_SEVEN:
		case CELL_PICK_EIGHT:
		case GAME_OVER_PLAYER:
		case GAME_OVER_COMPUTER:
		case GAME_OVER_TIE:
			Events.push_back(packet.packet_type);
			break;
		default:
			printf("Unsupported Packet Type\n");
			break;
		}
	}
}

