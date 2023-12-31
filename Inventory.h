#ifndef LMD_GAMELOGIC_INVENTORY
#define LMD_GAMELOGIC_INVENTORY

#include <string>
#include <vector>

#include "Player.h"
#include "Item.h"
#include "ConsumableItem.h"
#include "InformationItem.h"
#include "PowerupItem.h"


namespace GameLogic
{
	class Inventory
	{
	public:
		Inventory(Player player);
		void AddToInformationList(InformationItem information);
		void AddToConsumableList(ConsumableItem consumable);


	private:
		std::vector<InformationItem> _informationList;
		std::vector<ConsumableItem> _consumableList;
		Player _player;
	};
}

#endif // !LMD_GAMELOGIC_INVENTORY