#include "Inventory.h"

using namespace GameLogic;

Inventory::Inventory(Player player)
{
	_player = player;
}

void Inventory::AddToInformationList(InformationItem information)
{
	_informationList.push_back(information);
}

void Inventory::AddToConsumableList(ConsumableItem consumable)
{
	_consumableList.push_back(consumable);
}
