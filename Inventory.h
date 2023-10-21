#ifndef LMD_GAMELOGIC_INVENTORY
#define LMD_GAMELOGIC_INVENTORY

#include <string>
#include <vector>

#include "Entity.h"
#include "Item.h"
#include "ConsumableItem.h"
#include "InformationItem.h"
#include "PowerupItem.h"

class Inventory
{
public:
	Inventory();
	void AddToInformationList(InformationItem information);
	void AddToConsumableList(InformationItem information);
	

private:
	std::vector<InformationItem> _informationList;
	std::vector<ConsumableItem> _consumableList;
	Entity& _player;
};

#endif // !LMD_GAMELOGIC_INVENTORY