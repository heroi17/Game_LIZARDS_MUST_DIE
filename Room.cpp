#include "Room.h"

using namespace GameLogic;

Room::Room()
{

}

Room::Room(std::vector<Entity> enemies, Item rewardItem)
{
	_enemies = enemies;
	_rewardItem = rewardItem;
}
