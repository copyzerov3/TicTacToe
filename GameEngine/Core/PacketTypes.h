#include <string.h>

#define MAX_PACKET_SIZE 10000

enum PacketTypes
{
	INIT_CONNECTION = 9,
	CELL_PICK_ZERO = 0,
	CELL_PICK_ONE = 1,
	CELL_PICK_TWO = 2,
	CELL_PICK_THREE = 3,
	CELL_PICK_FOUR = 4,
	CELL_PICK_FIVE = 5,
	CELL_PICK_SIX = 6,
	CELL_PICK_SEVEN = 7,
	CELL_PICK_EIGHT = 8,
	RESTART_GAME = 10,
	GAME_OVER_PLAYER = 11,
	GAME_OVER_COMPUTER = 12,
	GAME_OVER_TIE = 13,
};

struct Packet
{
	unsigned int packet_type;

	void Serialize(char* Data)
	{
		memcpy(Data, this, sizeof(Packet));
	}
	void Deserialize(char* Data)
	{
		memcpy(this, Data, sizeof(Packet));
	}
};