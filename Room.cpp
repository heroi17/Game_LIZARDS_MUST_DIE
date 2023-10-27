#include "Room.h"

using namespace GameLogic;

GameLogic::Room::Room()
{

}

GameLogic::Room::Room(std::vector<Entity> enemies, Item rewardItem)
{
	_enemies = enemies;
	_rewardItem = rewardItem;
}

GameLogic::Room::Room(const Room& otherRoom)
{
	_enemies = otherRoom._enemies;
	_rewardItem = otherRoom._rewardItem;
}
