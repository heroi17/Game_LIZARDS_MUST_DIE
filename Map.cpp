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

size_t Map::GetWidth()
{
	return _width;
}

Room& Map::GetRoom(int row, int column)
{
	return _rooms[_width * row + column];
}

void Map::fillRooms()
{
}
