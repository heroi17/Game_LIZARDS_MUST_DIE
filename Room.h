#ifndef LMD_GAMELOGIC_ROOM
#define LMD_GAMELOGIC_ROOM

#include <vector>

#include "Item.h"
#include "Entity.h"
#include "Lizard.h"

namespace GameLogic
{
	class Room
	{
	public:
		Room();
		~Room();
		Room(std::vector<Entity*> enemies, Item* rewardItem);
		Room(const Room& otherRoom);

		Room& operator=(const Room& otherRoom);

	private:
		std::vector<Entity*> _enemies;
		Item* _rewardItem;
	};
}
#endif // !LMD_GAMELOGIC_ROOM
