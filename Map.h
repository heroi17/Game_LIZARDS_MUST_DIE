#ifndef LMD_GAMELOGIC_MAP
#define LMD_GAMELOGIC_MAP

#include "Room.h"

class Map
{
public:
	Map();
	Map(size_t width, size_t height);
	
	size_t GetHeight();
	size_t GetWidth();

	void SetHeight();
	void SetWidth();

private:
	size_t _height; // Number of rooms in one column
	size_t _width; // Number of rooms in one row
	Room* _rooms; // Array of elements of the Room class
	void fillRooms();
};

#endif // !LMD_GAMELOGIC_MAP

