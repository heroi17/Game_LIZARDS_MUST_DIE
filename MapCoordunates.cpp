#include "MapCoordunates.h"

GameLogic::MapCoordinates::MapCoordinates()
{
	X = 0;
	Y = 0;
}

GameLogic::MapCoordinates::MapCoordinates(size_t x, size_t y)
{
	X = x;
	Y = y;
}

bool GameLogic::MapCoordinates::operator<(const MapCoordinates& mapCoordinates) const
{
	if (X < mapCoordinates.X && Y <= mapCoordinates.Y)
	{
		return true;
	}
	return false;
}
