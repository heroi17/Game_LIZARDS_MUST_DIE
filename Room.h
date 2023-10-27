#ifndef LMD_GAMELOGIC_ROOM
#define LMD_GAMELOGIC_ROOM

#include <vector>

#include "Item.h"
#include "Entity.h"

namespace GameLogic
{
	class Room
	{
	public:
		Room();
		Room(std::vector<Entity> enemies, Item rewardItem);
		Room(const Room& otherRoom);


	private:
		Room& operator=(const Room& other);
		std::vector<Entity> _enemies;
		Item _rewardItem;
	};
}
#endif // !LMD_GAMELOGIC_ROOM
