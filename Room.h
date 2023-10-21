#ifndef LMD_GAMELOGIC_ROOM
#define LMD_GAMELOGIC_ROOM

#include <vector>

#include "Item.h"
#include "Entity.h"

class Room
{
public:
	Room();
	Room(std::vector<Entity> enemies, Item rewardItem);

private:
	std::vector<Entity> _enemies;
	Item _rewardItem;
};

#endif // !LMD_GAMELOGIC_ROOM
