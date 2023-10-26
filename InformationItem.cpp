#include "InformationItem.h"


using namespace GameLogic;

InformationItem::InformationItem(std::string name, std::string discription, InformationItemType type, Map& map) : _map(map)
{
	_name = name;
	_discription = discription;
	_type = type;
	_lastPowerUpIndex = 0;
}

void InformationItem::ApplyEffect(Entity& entity) 
{
	switch (_type)
	{
		case LeaderLocation:
		{
			_map.GetLeaderLocation();
		}
		case PowerUpLocation:
		{
			_map.GetPowerUpLocation(_lastPowerUpIndex);
		}
	}
}
