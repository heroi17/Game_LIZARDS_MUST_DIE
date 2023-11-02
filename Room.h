#ifndef LMD_GAMELOGIC_ROOM
#define LMD_GAMELOGIC_ROOM

#include <vector>

#include "PhysSimulation.h" 
#include "Item.h"
#include "Entity.h"
#include "Lizard.h"


namespace GameLogic
{
	class Room
	{
	public:
		Room();
		Room(std::vector<Entity*> enemies, Item* rewardItem);
		Room(const Room& otherRoom);
		~Room();
		Room& operator=(const Room& otherRoom);

		Item* GetRewardItem();
		std::vector<Entity*> GetEnemies();

		void Show();
	private:
		std::vector<Entity*> _enemies;
		Item* _rewardItem;
		PSimulation::simulation_room* _simulationRoom;
	};
}
#endif // !LMD_GAMELOGIC_ROOM
