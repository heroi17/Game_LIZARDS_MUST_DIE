#include "InformationItem.h"
#include <iostream>

using namespace GameLogic;

InformationItem::InformationItem(std::string name, std::string discription, InformationItemType type, Map* map)
{
	_map = map;
	_name = name;
	_discription = discription;
	_type = type;
}

void InformationItem::ApplyEffect(Entity* entity) 
{
	switch (_type)
	{
		case LeaderLocation:
		{
			std::cout << "Leadder is located in the (" << _map->GetLeaderLocation().first << ',' << _map->GetLeaderLocation().second << ") room" << std::endl;;
			break;
		}
	}
}
