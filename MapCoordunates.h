#ifndef LMD_GAMELOGIC_MAP_COORDINATES
#define LMD_GAMELOGIC_MAP_COORDINATES

namespace GameLogic
{
	typedef struct MapCoordinates
	{
		MapCoordinates();
		MapCoordinates(size_t x, size_t y);
		bool operator < (const MapCoordinates& mapcoordinates) const;
		size_t X;
		size_t Y;
	}MapCoordinates;
}
#endif // !LMD_GAMELOGIC_MAP_COORDINATES