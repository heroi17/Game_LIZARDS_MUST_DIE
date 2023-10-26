#include "Map.h"

using namespace GameLogic;

Map::Map(size_t width, size_t height)
{
	_height = height;
	_width = width;
}

size_t Map::GetHeight()
{
	return _height;
}

size_t Map::GetWidth() {return _width;}

Room& Map::GetRoom(size_t row, size_t column)
{
	MapCoordinates mapCoordinates(column, row);
	return _rooms[mapCoordinates];
}

MapCoordinates GameLogic::Map::GetLeaderLocation()
{
	return LeaderLocation;
}

MapCoordinates GameLogic::Map::GetPowerUpLocation(size_t index)
{
	if (index < PowerupLocation.size())
		return PowerupLocation[index];
	return PowerupLocation[0];
}

void Map::fillRooms()
{
}
