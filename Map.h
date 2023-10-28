#ifndef LMD_GAMELOGIC_MAP
#define LMD_GAMELOGIC_MAP

#include <map>
#include <utility>

#include "Room.h"

namespace GameLogic
{
	class Map
	{
	public:
		Map(size_t width = 5, size_t height = 5);
		~Map();

		size_t GetHeight();
		size_t GetWidth();

		Room* GetRoom(size_t row, size_t column);

		std::pair<size_t, size_t> GetLeaderLocation();

		void SetLeaderLocation(std::pair<size_t, size_t> coordinates);

	private:
		size_t _height; // Number of rooms in one column
		size_t _width; // Number of rooms in one row
		
		std::map<std::pair<size_t, size_t>, Room*> _rooms; // Array of elements of the Room class
		
		std::pair<size_t, size_t> _leaderLocation; // a coordinate of the room where final boss of the game is located
		std::vector<std::pair<size_t, size_t>> _powerupLocation; // List of the coordinates of rooms where power up item is located

		void fillRooms(); // Method that fills _rooms grid with objects

	};
}
#endif // !LMD_GAMELOGIC_MAP

