#ifndef LMD_GAMELOGIC_MAP
#define LMD_GAMELOGIC_MAP

#include <map>

#include "Room.h"
#include "MapCoordunates.h"	

namespace GameLogic
{
	class Map
	{
	public:
		Map(size_t width = 5, size_t height = 5);

		size_t GetHeight();
		size_t GetWidth();

		Room& GetRoom(size_t row, size_t column);

		MapCoordinates GetLeaderLocation();
		MapCoordinates GetPowerUpLocation(size_t index);

	private:
		size_t _height; // Number of rooms in one column
		size_t _width; // Number of rooms in one row
		
		std::map<MapCoordinates, Room> _rooms; // Array of elements of the Room class
		
		MapCoordinates LeaderLocation; // a coordinate of the room where final boss of the game is located
		std::vector<MapCoordinates> PowerupLocation; // List of the coordinates of rooms where power up item is located

		void fillRooms(); // Method that fills _rooms grid with objects

	};
}
#endif // !LMD_GAMELOGIC_MAP

