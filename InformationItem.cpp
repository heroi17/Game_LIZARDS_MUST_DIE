#include "InformationItem.h"

#include "Map.h"

using namespace GameLogic;

InformationItem::InformationItem(std::string name, std::string discription, InformationItemType type)
{
	_name = name;
	_discription = discription;
	_type = type;
}

void InformationItem::ApplyEffect(Entity& entity) 
{
	switch (_type)
	{
		case LeaderLocation:
		{
			// Map.FindLeader()
		}
		case PowerUpLocation:
		{
			// Map.FindPowerup()
		}
	}
}
