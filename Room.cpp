#include "Room.h"

Room::Room()
{

}

Room::Room(std::vector<Entity> enemies, Item rewardItem)
{
	_enemies = enemies;
	_rewardItem = rewardItem;
}
