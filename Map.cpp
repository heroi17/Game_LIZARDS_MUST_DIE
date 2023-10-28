#include "Map.h"

#include "RoomGenerator.h"
#include "Lizard.h"

using namespace GameLogic;

Map::Map(size_t width, size_t height)
{
	_height = height;
	_width = width;
	_leaderLocation = std::make_pair(0, 0);
	_powerupLocation = std::vector<std::pair<size_t, size_t>>{};
}

GameLogic::Map::~Map()
{
	for (int i = 1; i <= _height; i++)
	{
		for (int j = 1; j <= _width; j++)
		{
			delete _rooms[std::make_pair(i, j)];
		}
	}
}

size_t Map::GetHeight()
{
	return _height;
}

size_t Map::GetWidth()
{
	return _width;
}

Room* Map::GetRoom(size_t row, size_t column)
{
	std::pair<size_t, size_t> mapCoordinates(column, row);
	return _rooms[mapCoordinates];
}

std::pair<size_t, size_t> GameLogic::Map::GetLeaderLocation()
{
	return _leaderLocation;
}

void GameLogic::Map::SetLeaderLocation(std::pair<size_t, size_t> coordinates)
{
	_leaderLocation = coordinates;
}

void Map::fillRooms()
{
	for (int i = 1; i <= _height; i++)
	{
		for (int j = 1; j <= _width; j++)
		{
			RoomGenerator roomgenerator(this);
			_rooms[std::make_pair(i, j)] = roomgenerator.GetRandomRoomPreset(std::make_pair(i,j));
		}
	}
}
