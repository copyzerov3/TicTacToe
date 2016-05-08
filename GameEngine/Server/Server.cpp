#include "Server.h"

unsigned int Server::client_ID;
Server::Server()
{
	client_ID = 0;
	Network = new ServerNetwork();
}


Server::~Server()
{
	delete Network;
	Network = NULL;
}

void Server::Update()
{
	if (Network->AcceptNewClient(client_ID))
	{
		printf("Client %d has been connected to the server\n", client_ID);

		client_ID++;
	}
	RecieveFromClients();
}

void Server::SendPacketToAll(unsigned int packetType)
{
	const unsigned int packetSize = sizeof(Packet);
	char packetData[packetSize];

	Packet packet;
	packet.packet_type = packetType;

	packet.Serialize(packetData);
	Network->SendToAllClients(packetData, packetSize);

}
void Server::RecieveFromClients()
{
	Packet packet;

	std::map<unsigned int, SOCKET>::iterator iter;

	for (iter = Network->Clients.begin(); iter != Network->Clients.end(); iter++)
	{
		int DataLength = Network->RecieveData(iter->first, NetworkData);

		if (DataLength <= 0)
		{
			continue;
		}
		int i = 0;
		while (i < (unsigned int)DataLength)
		{
			packet.Deserialize(&(NetworkData[i]));
			i += sizeof(Packet);
			switch (packet.packet_type)
			{
			case INIT_CONNECTION:
				printf("Server recieved INIT packet from client\n");
				break;
			case CELL_PICK_ZERO:
			case CELL_PICK_ONE:
			case CELL_PICK_TWO:
			case CELL_PICK_THREE:
			case CELL_PICK_FOUR:
			case CELL_PICK_FIVE:
			case CELL_PICK_SIX:
			case CELL_PICK_SEVEN:
			case CELL_PICK_EIGHT:
				Events.push_back(packet.packet_type);
				printf("RECIEVED CELL %d\n", packet.packet_type);
				break;
			case RESTART_GAME:
				Events.push_back(packet.packet_type);
				printf("RESTARTING GAME:");
			default:
				printf("ERROR IN PACKET TYPE\n");
				break;
			}
		}
	}
}
