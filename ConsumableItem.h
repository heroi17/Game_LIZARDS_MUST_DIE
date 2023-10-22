#ifndef LMD_GAMELOGIC_CONSUMABLEITEM
#define LMD_GAMELOGIC_CONSUMABLEITEM

#include "Item.h"

enum ConsumableItemType
{
	HealingItem_30,
	HealingItem_50,
	HealingItem_100
};

class ConsumableItem : Item
{
public:
	ConsumableItem(std::string name, std::string discription, ConsumableItemType type);

private:
	ConsumableItemType _type;
};



#endif // !LMD_GAMELOGIC_CONSUMABLEITEM
