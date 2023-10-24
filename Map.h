#ifndef LMD_GAMELOGIC_MAP
#define LMD_GAMELOGIC_MAP

#include "Room.h"

namespace GameLogic
{
	class Map
	{
	public:
		Map(size_t width = 5, size_t height = 5);

		size_t GetHeight();
		size_t GetWidth();

		Room& GetRoom(int row, int column);

	private:
		size_t _height; // Number of rooms in one column
		size_t _width; // Number of rooms in one row
		Room* _rooms; // Array of elements of the Room class
		void fillRooms(); // Method that fills _rooms grid with objects
	};
}
#endif // !LMD_GAMELOGIC_MAP

