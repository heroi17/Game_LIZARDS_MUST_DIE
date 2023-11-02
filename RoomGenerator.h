#ifndef LMD_GAMELOGIC_ROOM_GENERATOR
#define LMD_GAMELOGIC_ROOM_GENERATOR

#include "Room.h"
#include "Item.h"
#include "PowerupItem.h"
#include "ConsumableItem.h"
#include "InformationItem.h"
#include "Entity.h"
#include "Lizard.h"


namespace GameLogic
{
	class RoomGenerator
	{
	public:
		RoomGenerator(Map* map);
		Room* GetRandomRoomPreset(std::pair<size_t, size_t>);
	private:
		Item* GetRandomItemPreset();
		Lizard* GetRandomLizardPreset();
		
		static bool isLeaderSpawned;
		Map* _map;
	};
}

#endif